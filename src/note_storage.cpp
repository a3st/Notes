#include "note_storage.hpp"
#include "precompiled.hpp"
#include <base64pp/base64pp.h>

#include "exporters/txt.hpp"

namespace notes
{
    NoteStorage::NoteStorage() : database("notes.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
    {
        if (!this->tryCreateNotesDB())
        {
            throw std::runtime_error("An error occurred when adding a new table to the database");
        }
    }

    std::vector<Note> NoteStorage::loadNotesFromDB() const
    {
        std::vector<Note> notes;

        std::string const dbSelectSQL("SELECT `id` ,`name`, `data` FROM `notes`");

        SQLite::Statement query(database, dbSelectSQL);
        while (query.executeStep())
        {
            uint32_t const noteID = query.getColumn(0).getInt();
            std::string const noteName = query.getColumn(1).getString();
            std::string const noteData = query.getColumn(2).getString();

            notes.emplace_back(noteID, noteName, noteData);
        }
        return notes;
    }

    bool NoteStorage::tryCreateNotesDB()
    {
        if (database.tableExists("notes"))
        {
            return true;
        }

        std::string const dbCreateSQL("CREATE TABLE `notes` (`id` INTEGER PRIMARY KEY, `name` TEXT, `data` BLOB)");

        int32_t result = database.tryExec(dbCreateSQL);
        if (result != SQLite::OK)
        {
            return false;
        }

        std::string const noteName = "Первая заметка";
        std::string const noteData =
            R"(IyDQn9GA0LjQstC10YIhCiMjIyDQrdGC0L4g0L/QtdGA0LLQsNGPINC30LDQvNC10YLQutCwINCyINGA0LDQt9C80LXRgtC60LUgTWFya2Rvd24KCtCQINC90LjQttC1INC/0YDQtdC00YHRgtCw0LLQu9C10L0g0L7QsdGL0YfQvdGL0Lkg0YHQv9C40YHQvtC6INC30LDQtNCw0YcsINC60L7RgtC+0YDRi9C1INC90LXQvtCx0YXQvtC00LjQvNC+INCx0YvQu9C+INGA0LXQsNC70LjQt9C+0LLQsNGC0YwKCtCh0L/QuNGB0L7QuiDQt9Cw0LTQsNGHOgoKMS4g0JTQvtC00LXQu9Cw0YLRjCBVSSDQt9Cw0LzQtdGC0L7QujsKMi4g0J/QvtC00LrQu9GO0YfQuNGC0YwgU1FMaXRlINCyINC60LDRh9C10YHRgtCy0LUg0JHQlDsKMy4g0KDQtdCw0LvQuNC30L7QstCw0YLRjCDQstC30LDQuNC80L7QtNC10LnRgdGC0LLQuNC1ICpCYWNrZW5kKiDQuCAqRnJvbnRlbmQqINC/0YDQuNC70L7QttC10L3QuNGPINGH0LXRgNC10Lcg0LfQsNC/0YDQvtGB0Ysg0LIgKkpTT04qINGE0L7RgNC80LDRgtC1CgrQkCDQstC+0YIg0YHRgtGA0L7QutCwINC90LAgKlB5dGhvbio6IGBwcmludCgiSGVsbG8gd29ybGQhIilgCgohW2xpYndlYnZpZXddKGh0dHBzOi8vZ2l0aHViLmNvbS9hM3N0L2xpYndlYnZpZXcvcmF3L21haW4vbWVkaWEvc3BsYXNoLW1haW4ucG5nKQ==)";

        std::string const dbAddFirstNoteSQL =
            std::format("INSERT INTO `notes` (`name`, `data`) VALUES ('{}', '{}')", noteName, noteData);

        database.exec(dbAddFirstNoteSQL);
        return true;
    }

    int32_t NoteStorage::saveNoteToDB(Note const& note)
    {
        std::string const dbCheckNoteSQL = std::format("SELECT count(*) FROM `notes` WHERE `id`={}", note.noteID);

        int32_t const numNotes = database.execAndGet(dbCheckNoteSQL).getInt();
        if (numNotes == 0)
        {
            std::string const dbAddNoteSQL = std::format(
                "INSERT INTO `notes` (`name`, `data`) VALUES ('{}', '{}') RETURNING id", note.noteName, note.noteData);

            return database.execAndGet(dbAddNoteSQL).getInt();
        }
        else
        {
            std::string const dbUpdateNoteSQL = std::format("UPDATE `notes` SET `name`='{}', `data`='{}' WHERE `id`={}",
                                                            note.noteName, note.noteData, note.noteID);

            int32_t const result = database.tryExec(dbUpdateNoteSQL);
            if (result != SQLite::OK)
            {
                throw std::runtime_error("An error occurred when updating a row to the database");
            }

            return note.noteID;
        }
    }

    void NoteStorage::removeNoteFromDB(uint32_t const ID)
    {
        std::string const dbDeleteSQL = std::format("DELETE FROM `notes` WHERE `id`={}", ID);

        int32_t const result = database.tryExec(dbDeleteSQL);
        if (result != SQLite::OK)
        {
            throw std::runtime_error("An error occurred when updating a row to the database");
        }
    }

    std::string NoteStorage::getNotesData() const
    {
        std::stringstream stream;
        stream << "{\"notes\":[";

        bool isFirst = true;
        for (auto const& note : this->loadNotesFromDB())
        {
            if (!isFirst)
            {
                stream << ",";
            }
            stream << note.dump();
            isFirst = false;
        }
        stream << "]}";
        return stream.str();
    }

    bool NoteStorage::exportNoteAsFile(uint32_t const ID, std::string_view const format,
                                       std::filesystem::path const& filePath)
    {
        std::string const dbSelectSQL = std::format("SELECT `name`, `data` FROM `notes` WHERE `id`={}", ID);

        SQLite::Statement query(database, dbSelectSQL);

        Note note;
        if (query.executeStep())
        {
            std::string const noteName = query.getColumn(0).getString();
            std::string const noteData = query.getColumn(1).getString();

            note.noteID = ID;
            note.noteName = noteName;
            note.noteData = noteData;
        }

        if (query.hasRow())
        {
            std::unique_ptr<Exporter> exporter;

            std::string text;

            auto result = base64pp::decode(note.noteData);
            if (!result.has_value())
            {
                text = "";
            }
            else
            {
                auto decodedData = result.value();
                text = std::string(reinterpret_cast<char const*>(decodedData.data()), decodedData.size());
            }

            if (format.compare("txt") == 0)
            {
                exporter = std::make_unique<exporters::TxtExport>(text);
            }

            return exporter->saveFileAs(filePath);
        }
    }
} // namespace notes
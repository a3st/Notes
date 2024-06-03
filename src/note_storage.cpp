#include "note_storage.hpp"
#include "precompiled.hpp"

namespace notes
{
    NoteStorage::NoteStorage() : database("notes.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
    {
        if (!this->tryCreateNotesDB())
        {
            throw std::runtime_error("An error occurred when adding a new table to the database");
        }

        this->loadNotesFromDB();
    }

    void NoteStorage::loadNotesFromDB()
    {
        notes.clear();

        std::string const dbSelectSQL("SELECT `id` ,`name`, `data` FROM `notes`");

        SQLite::Statement query(database, dbSelectSQL);
        while (query.executeStep())
        {
            uint32_t const noteID = query.getColumn(0).getInt();
            std::string const noteName = query.getColumn(1).getString();
            std::string const noteData = query.getColumn(2).getString();

            notes.emplace_back(noteID, noteName, noteData);
        }
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

    void NoteStorage::saveNoteToDB(Note const& note)
    {
        std::string const dbCheckNoteSQL = std::format("SELECT count(*) FROM `notes` WHERE `id`={}", note.noteID);

        int32_t const numNotes = database.execAndGet(dbCheckNoteSQL).getInt();
        if (numNotes == 0)
        {
            std::string const dbAddNoteSQL = std::format(
                "INSERT INTO `notes` (`name`, `data`) VALUES ('{}', '{}') RETURNING id", note.noteName, note.noteData);

            uint32_t const noteID = database.execAndGet(dbAddNoteSQL).getInt();

            notes.emplace_back(noteID, note.noteName, note.noteData);
        }
        else
        {
            std::string const dbUpdateNoteSQL = std::format("UPDATE `notes` SET `name`='{}', `data`='{}' WHERE `id`={}",
                                                            note.noteName, note.noteData, note.noteID);

            int32_t result = database.tryExec(dbUpdateNoteSQL);
            if (result != SQLite::OK)
            {
                throw std::runtime_error("An error occurred when updating a row to the database");
            }

            auto found = std::find_if(notes.begin(), notes.end(),
                                      [&](auto const& element) { return note.noteID == element.noteID; });
            if (found != notes.end())
            {
                found->noteName = note.noteName;
                found->noteData = note.noteData;
            }
        }
    }

    std::string NoteStorage::getNotesData() const
    {
        std::stringstream stream;

        stream << "{\"notes\":[";
        bool isFirst = true;
        for (auto const& note : notes)
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
} // namespace notes
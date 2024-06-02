#include "app.hpp"
#include "precompiled.hpp"
#include <base64pp/base64pp.h>

namespace notes
{
    App::App()
        : database("notes.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE),
          app("notes-app", "Notes", 580, 600, true, true)
    {
        if (!this->tryCreateNotesDB())
        {
            throw std::runtime_error("An error occurred when adding a new table to the database");
        }

        app.bind<uint32_t, std::string, uint32_t>("test", [&](libwebview::EventArgs const& e, int32_t a1, std::string a2, uint32_t a3) {
            std::cout << a2 << std::endl;
        });

        /*app.bind("getNotesFromDB", [&](libwebview::EventArgs const& args) {
            if(this->loadNotesFromDB()) {

                
            }
        });*/
    }

    int32_t App::run(int32_t const argc, char** argv)
    {
        app.run("resources/index.html");
        return EXIT_SUCCESS;
    }

    bool App::loadNotesFromDB()
    {
        if (database.tableExists("notes"))
        {
            return false;
        }

        std::string const dbSelectSQL("SELECT `name`, `data` FROM `notes`");

        SQLite::Statement query(database, dbSelectSQL);
        while (query.executeStep())
        {
            std::string const noteName = query.getColumn(0).getString();
            std::string const noteData = query.getColumn(1).getString();

            auto note = std::make_unique<Note>(noteName, noteData);
            notes.emplace_back(std::move(note));
        }
        return true;
    }

    bool App::tryCreateNotesDB()
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
            "IyDQn9GA0LjQstC10YIhCiMjIyDQrdGC0L4g0L/"
            "QtdGA0LLQsNGPINC30LDQvNC10YLQutCwINCyINGA0LDQt9C80LXRgtC60LUgTWFya2Rvd24KCtCQINC90LjQttC1INC/"
            "0YDQtdC00YHRgtCw0LLQu9C10L0g0L7QsdGL0YfQvdGL0Lkg0YHQv9C40YHQvtC6INC30LDQtNCw0YcsINC60L7RgtC+"
            "0YDRi9C1INC90LXQvtCx0YXQvtC00LjQvNC+INCx0YvQu9C+INGA0LXQsNC70LjQt9C+0LLQsNGC0YwKCtCh0L/"
            "QuNGB0L7QuiDQt9Cw0LTQsNGHOgoKMS4g0JTQvtC00LXQu9Cw0YLRjCBVSSDQt9Cw0LzQtdGC0L7QujsKMi4g0J/"
            "QvtC00LrQu9GO0YfQuNGC0YwgU1FMaXRlINCyINC60LDRh9C10YHRgtCy0LUg0JHQlDsKMy4g0KDQtdCw0LvQuNC30L7QstCw0YLRjCDQs"
            "tC30LDQuNC80L7QtNC10LnRgdGC0LLQuNC1ICpCYWNrZW5kKiDQuCAqRnJvbnRlbmQqINC/"
            "0YDQuNC70L7QttC10L3QuNGPINGH0LXRgNC10Lcg0LfQsNC/"
            "0YDQvtGB0Ysg0LIgKkpTT04qINGE0L7RgNC80LDRgtC1CgrQkCDQstC+"
            "0YIg0YHRgtGA0L7QutCwINC90LAgKlB5dGhvbio6IGBwcmludCgiSGVsbG8gd29ybGQhIilgCgohW2xpYndlYnZpZXddKGh0dHBzOi8vZ2"
            "l0aHViLmNvbS9hM3N0L2xpYndlYnZpZXcvcmF3L21haW4vc3BsYXNoLW1haW4ucG5nKQ==";

        std::string const dbAddFirstNoteSQL =
            std::format("INSERT INTO `notes` (`name`, `data`) VALUES ('{}', '{}')", noteName, noteData);

        database.exec(dbAddFirstNoteSQL);
        return true;
    }
} // namespace notes
#pragma once

#include "note.hpp"
#include "webview.hpp"
#include <SQLiteCpp/SQLiteCpp.h>

namespace notes
{
    class App
    {
      public:
        App();

        int32_t run(int32_t const argc, char** argv);

      private:
        libwebview::App app;
        SQLite::Database database;
        std::vector<std::unique_ptr<Note>> notes;

        bool loadNotesFromDB();
        bool tryCreateNotesDB();
    };
} // namespace notes
#pragma once

#include "note.hpp"
#include <SQLiteCpp/SQLiteCpp.h>

namespace notes
{
    class NoteStorage
    {
      public:
        NoteStorage();

        std::string getNotesData() const;

        void saveNoteToDB(Note const& note);

      private:
        SQLite::Database database;
        std::vector<Note> notes;

        void loadNotesFromDB();
        bool tryCreateNotesDB();
    };
} // namespace notes
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

        void removeNoteFromDB(uint32_t const ID);

      private:
        SQLite::Database database;

        std::vector<Note> loadNotesFromDB() const;
        bool tryCreateNotesDB();
    };
} // namespace notes
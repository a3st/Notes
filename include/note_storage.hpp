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

        int32_t saveNoteToDB(Note const& note);

        void removeNoteFromDB(uint32_t const ID);

        bool exportNoteAsFile(uint32_t const ID, std::string_view const format, std::filesystem::path const& filePath);

      private:
        SQLite::Database database;

        std::vector<Note> loadNotesFromDB() const;
        bool tryCreateNotesDB();
    };
} // namespace notes
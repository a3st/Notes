#pragma once

#include "note_storage.hpp"
#include <webview.hpp>

namespace notes
{
    class ViewModel
    {
      public:
        ViewModel(libwebview::App* app);

        std::string getNotes();

        int32_t saveNote(uint32_t ID, std::string noteName, std::string noteData);

        void removeNote(uint32_t ID);

        void exportNote(uint32_t ID, std::string format);

      private:
        libwebview::App* app;
        NoteStorage noteStorage;
    };
} // namespace notes
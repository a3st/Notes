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

        void saveNote(uint32_t ID, std::string noteName, std::string noteData);

      private:
        libwebview::App* app;
        NoteStorage noteStorage;
    };
} // namespace notes
#include "view_model.hpp"
#include "precompiled.hpp"

namespace notes
{
    ViewModel::ViewModel(libwebview::App* app)
    {
        app->bind("getNotes", [this]() -> std::string { return getNotes(); });
        app->bind("saveNote", [this](uint32_t ID, std::string noteName, std::string noteData) -> void {
            saveNote(ID, noteName, noteData);
        });
        app->bind("removeNote", [this](uint32_t ID) -> void { removeNote(ID); });
    }

    std::string ViewModel::getNotes()
    {
        return noteStorage.getNotesData();
    }

    void ViewModel::saveNote(uint32_t ID, std::string noteName, std::string noteData)
    {
        noteStorage.saveNoteToDB(Note(ID, noteName, noteData));
    }

    void ViewModel::removeNote(uint32_t ID)
    {
        noteStorage.removeNoteFromDB(ID);
    }
} // namespace notes
#include "view_model.hpp"
#include "precompiled.hpp"

namespace notes
{
    ViewModel::ViewModel(libwebview::App* app) : app(app)
    {
        app->bind("getNotes", [this]() -> std::string { return getNotes(); });
        app->bind("saveNote", [this](uint32_t ID, std::string noteName, std::string noteData) -> int32_t {
            return saveNote(ID, noteName, noteData);
        });
        app->bind("removeNote", [this](uint32_t ID) -> void { removeNote(ID); });
        app->bind("exportNote", [this](uint32_t ID, std::string format) -> void { exportNote(ID, format); });
    }

    std::string ViewModel::getNotes()
    {
        return noteStorage.getNotesData();
    }

    int32_t ViewModel::saveNote(uint32_t ID, std::string noteName, std::string noteData)
    {
        return noteStorage.saveNoteToDB(Note(ID, noteName, noteData));
    }

    void ViewModel::removeNote(uint32_t ID)
    {
        noteStorage.removeNoteFromDB(ID);
    }

    void ViewModel::exportNote(uint32_t ID, std::string format)
    {
        auto result = app->showSaveDialog(std::filesystem::current_path(), "");
        if (result.has_value())
        {
            if (!noteStorage.exportNoteAsFile(ID, format, result.value()))
            {
                libwebview::showMessageDialog("Notes",
                                              "Произошла ошибка во время сохранения файла. Попробуйте еще раз!",
                                              libwebview::MessageDialogType::Error);
            }
        }
    }
} // namespace notes
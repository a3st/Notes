#include "note.hpp"
#include "precompiled.hpp"

namespace notes
{
    Note::Note(uint32_t const noteID, std::string_view const noteName, std::string_view const noteData)
        : noteID(noteID), noteName(noteName), noteData(noteData)
    {
    }

    std::string Note::dump() const
    {
        std::stringstream stream;
        stream << "{\"id\":" << std::to_string(noteID) << ",\"name\":\"" << noteName << "\",data:\"" << noteData
               << "\"}";
        return stream.str();
    }
} // namespace notes
#include "note.hpp"
#include "precompiled.hpp"

namespace notes
{
    Note::Note(const std::string_view noteName, const std::string_view noteData)
        : noteName(noteName), noteData(noteData)
    {
    }

    std::string Note::dump()
    {
        std::stringstream stream;
        stream << "{\"name\":\"" << noteName << "\",data:\"" << noteData << "\"}";
        return stream.str();
    }

    std::string_view Note::getName() const
    {
        return noteName;
    }

    std::string_view Note::getData() const
    {
        return noteData;
    }
} // namespace notes
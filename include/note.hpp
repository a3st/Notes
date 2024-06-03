#pragma once

namespace notes
{
    struct Note
    {
        Note() = default;

        Note(uint32_t const noteID, std::string_view const noteName, std::string_view const noteData);

        /*!
          @brief Present note in JSON format
          @return JSON formatted string
        */
        std::string dump() const;

        uint32_t noteID;
        std::string noteName;
        std::string noteData;
    };
} // namespace notes
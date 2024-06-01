#pragma once

namespace notes
{
    class Note
    {
      public:
        Note(const std::string_view noteName, const std::string_view noteData);

        /*!
          @brief Present note in JSON format
          @return JSON formatted string
        */
        std::string dump();

        /*!
          @brief Get note name
          @return Note name
        */
        std::string_view getName() const;

        /*!
          @brief Get note data in base64 format
          @return Base64 formatted string
        */
        std::string_view getData() const;

      private:
        std::string noteName;
        std::string noteData;
    };
} // namespace notes
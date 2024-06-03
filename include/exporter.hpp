#pragma once

namespace notes
{
    class Exporter
    {
      public:
        virtual bool saveFileAs(std::filesystem::path const& filePath) = 0;
    };
} // namespace notes
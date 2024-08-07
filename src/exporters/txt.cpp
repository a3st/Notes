// Copyright © 2022-2024 Dmitriy Lukovenko. All rights reserved.

#include "exporters/txt.hpp"
#include "precompiled.hpp"

namespace notes::exporters
{
    TxtExport::TxtExport(std::string_view const text) : text(text)
    {
    }

    bool TxtExport::saveFileAs(std::filesystem::path const& filePath)
    {
        std::ofstream stream(filePath, std::ios::out);
        if (!stream.is_open())
        {
            return false;
        }

        stream << text;
        return true;
    }
} // namespace notes::exporters
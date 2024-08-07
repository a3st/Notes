// Copyright © 2022-2024 Dmitriy Lukovenko. All rights reserved.

#pragma once

namespace notes
{
    class Exporter
    {
      public:
        virtual bool saveFileAs(std::filesystem::path const& filePath) = 0;
    };
} // namespace notes
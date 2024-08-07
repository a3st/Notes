// Copyright © 2022-2024 Dmitriy Lukovenko. All rights reserved.

#pragma once

#include "exporter.hpp"

namespace notes::exporters
{
    class TxtExport : public Exporter
    {
      public:
        TxtExport(std::string_view const text);

        bool saveFileAs(std::filesystem::path const& filePath) override;

      private:
        std::string text;
    };
} // namespace notes::exporters
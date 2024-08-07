// Copyright © 2022-2024 Dmitriy Lukovenko. All rights reserved.

#include "precompiled.hpp"
#include "view_model.hpp"
#include <webview.hpp>

int32_t main(int32_t argc, char** argv)
{
    try
    {
        libwebview::App app("app.dl.notes", "Notes", 580, 600, true, false);
        app.setWindowMinSize(580, 600);

        notes::ViewModel viewModel(&app);

        app.run("resources/index.html");
        return EXIT_SUCCESS;
    }
    catch (std::exception e)
    {
        libwebview::showMessageDialog("Notes", e.what(), libwebview::MessageDialogType::Error);
        return EXIT_FAILURE;
    }
}
#include "precompiled.hpp"
#include "view_model.hpp"
#include <webview.hpp>

int32_t main(int32_t argc, char** argv)
{
    try
    {
        libwebview::App app("notes-app", "Notes", 580, 600, true, true);
        app.setMinWindowSize(580, 600);

        notes::ViewModel viewModel(&app);

        app.run("resources/index.html");
        return EXIT_SUCCESS;
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
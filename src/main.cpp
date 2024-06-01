#include "app.hpp"
#include "precompiled.hpp"

int32_t main(int32_t argc, char** argv)
{
    try
    {
        notes::App app;
        return app.run(argc, argv);
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
cmake_minimum_required(VERSION 3.26.0)
project(Notes VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT TARGET simdjson)
add_subdirectory(thirdparty/simdjson)
endif()

if (NOT TARGET libwebview_edge_static)
add_subdirectory(thirdparty/libwebview)
endif()

if (NOT TARGET SQLiteCpp)
add_subdirectory(thirdparty/SQLiteCpp)
endif()

if (NOT TARGET base64pp)
add_subdirectory(thirdparty/base64pp)
endif()

add_executable(Notes
    src/exporters/txt.cpp
    src/main.cpp
    src/view_model.cpp
    src/note_storage.cpp
    src/note.cpp
    app.rc)

if(WIN32)
set_target_properties(Notes
    PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
        LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
        LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
    )
endif()

target_include_directories(Notes PRIVATE 
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include)

target_precompile_headers(Notes PRIVATE ${PROJECT_SOURCE_DIR}/include/precompiled.hpp)
    
target_link_libraries(Notes PUBLIC
    base64pp
    SQLiteCpp
    simdjson
    libwebview_edge_static)

add_custom_command(
    TARGET Notes 
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/ui/dist ${PROJECT_BINARY_DIR}/resources)
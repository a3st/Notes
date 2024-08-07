# Copyright © 2022-2024 Dmitriy Lukovenko. All rights reserved.

cmake_minimum_required(VERSION 3.25.1)

project(Notes 
    VERSION 1.0.0 
    DESCRIPTION "Minimalistic note editor in Markdown format"
    HOMEPAGE_URL https://github.com/a3st/Notes
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/simdjson)

FetchContent_Declare(libwebview
    GIT_REPOSITORY https://github.com/a3st/libwebview.git
    GIT_TAG main
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/libwebview)

FetchContent_Declare(SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/SQLiteCpp)

FetchContent_Declare(base64pp
    GIT_REPOSITORY https://github.com/matheusgomes28/base64pp.git
    GIT_TAG main
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/base64pp)

FetchContent_MakeAvailable(simdjson libwebview SQLiteCpp base64pp)

add_executable(Notes
    src/exporters/txt.cpp
    src/main.cpp
    src/view_model.cpp
    src/note_storage.cpp
    src/note.cpp)

target_include_directories(Notes PRIVATE 
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include)

target_precompile_headers(Notes PRIVATE ${PROJECT_SOURCE_DIR}/include/precompiled.hpp)
    
target_link_libraries(Notes PRIVATE
    base64pp
    SQLiteCpp
    simdjson
    libwebview)

if(WIN32)
    set_target_properties(Notes
        PROPERTIES
            LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
            LINK_FLAGS_RELEASE "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
            LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
            LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
        )

    target_sources(Notes PRIVATE app.rc)
endif()

target_include_directories(Notes PRIVATE 
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/include)

target_precompile_headers(Notes PRIVATE ${PROJECT_SOURCE_DIR}/include/precompiled.hpp)
    
target_link_libraries(Notes PRIVATE
    base64pp
    SQLiteCpp
    simdjson
    libwebview)

add_custom_command(
    TARGET Notes 
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/ui/dist ${PROJECT_BINARY_DIR}/resources)
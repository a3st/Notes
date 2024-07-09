cmake_minimum_required(VERSION 3.25.1)

project(Notes VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(simdjson
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/simdjson
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/simdjson)

FetchContent_Declare(libwebview
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/libwebview
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/libwebview)

FetchContent_Declare(SQLiteCpp
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/SQLiteCpp
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/SQLiteCpp)

FetchContent_Declare(base64pp
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/base64pp
    BINARY_DIR ${CMAKE_BINARY_DIR}/thirdparty/base64pp)

FetchContent_MakeAvailable(simdjson libwebview SQLiteCpp base64pp)

add_executable(Notes
    src/exporters/txt.cpp
    src/main.cpp
    src/view_model.cpp
    src/note_storage.cpp
    src/note.cpp)

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
    libwebview_edge)

if(WIN32)
target_link_libraries(Notes PRIVATE libwebview_edge)
elseif(UNIX)
target_link_libraries(Notes PRIVATE libwebview_webkit)
endif()

add_custom_command(
    TARGET Notes 
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/ui/dist ${PROJECT_BINARY_DIR}/resources)
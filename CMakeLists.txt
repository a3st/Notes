cmake_minimum_required(VERSION 3.26.0)
project(Notes VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(thirdparty/simdjson)
add_subdirectory(thirdparty/libwebview)
add_subdirectory(thirdparty/SQLiteCpp)
add_subdirectory(thirdparty/base64pp)

add_executable(Notes
    src/main.cpp
    src/app.cpp
    src/note.cpp)

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
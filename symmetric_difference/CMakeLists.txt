cmake_minimum_required(VERSION 3.21)

project(
        symmdiff
        DESCRIPTION "Symmetric difference of two sets"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(symmdiff symmdiff.cpp)
add_executable(symmdiff_std symmdiff.cpp)

target_compile_definitions(symmdiff_std PRIVATE -DSTD)

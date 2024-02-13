cmake_minimum_required(VERSION 3.21)

project(
        symmdiff
        DESCRIPTION "Symmetrical difference of two arrays"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(symmdiff symmdiff.cpp)

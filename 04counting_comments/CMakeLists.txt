cmake_minimum_required(VERSION 3.21)

project(
        countcomm
        DESCRIPTION "4. Counting comments in Object Pascal"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(countcomm countcomm.cpp)

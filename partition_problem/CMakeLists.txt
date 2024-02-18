cmake_minimum_required(VERSION 3.21)

project(
        partition
        DESCRIPTION "Attempts to solver partition problem."
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(partition partition.cpp)

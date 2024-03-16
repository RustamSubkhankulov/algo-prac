cmake_minimum_required(VERSION 3.21)

project(
        partition
        DESCRIPTION "5. Attempts to solve partition problem."
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(partition partition.cpp)

set(ALGO_TYPES GREEDY PSEUDOPOLY KARMARKARA)

if(NOT ALGO_TYPE IN_LIST ALGO_TYPES)
    message(FATAL_ERROR "ALGO_TYPE must be one of ${ALGO_TYPES}")
endif()

target_compile_definitions(partition PRIVATE -D${ALGO_TYPE})
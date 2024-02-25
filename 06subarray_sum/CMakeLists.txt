cmake_minimum_required(VERSION 3.21)

project(
        subarray_sum
        DESCRIPTION "Max sum of subarray elements"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(ALGO_TYPES DUMB KADANE TAB)

if(NOT ALGO_TYPE IN_LIST ALGO_TYPES)
    message(FATAL_ERROR "ALGO_TYPE must be one of ${ALGO_TYPES}")
endif()

add_executable(subarray_sum subarray_sum.cpp)
target_compile_definitions(subarray_sum PRIVATE -D${ALGO_TYPE})

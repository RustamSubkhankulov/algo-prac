cmake_minimum_required(VERSION 3.21)

project(
        intersect
        DESCRIPTION "2. Intersection of two multisets"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(intersect multiset_intersection.cpp)
add_executable(intersect_std multiset_intersection.cpp)

target_compile_definitions(intersect_std PRIVATE -DSTD)

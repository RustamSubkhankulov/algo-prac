cmake_minimum_required(VERSION 3.21)

project(
        intersect
        DESCRIPTION "Polynomial calculation"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(polycalc polycalc.cpp)
add_executable(polycalc_stab polycalc.cpp)

target_compile_definitions(polycalc_stab PRIVATE -DSTAB)
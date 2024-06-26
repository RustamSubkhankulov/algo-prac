cmake_minimum_required(VERSION 3.21)

project(
        task
        DESCRIPTION "15. External sort"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "CMAKE_BUILD_TYPE is not specified, using Release by default")
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(EXEC_SRC_DIR src)
set(EXEC_INC_DIR inc)

file(GLOB EXEC_SOURCES CONFIGURE_DEPENDS ${EXEC_SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${EXEC_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${EXEC_INC_DIR})

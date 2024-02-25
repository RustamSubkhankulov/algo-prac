cmake_minimum_required(VERSION 3.21)

project(
        lint
        DESCRIPTION "Long integers library"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(LIB_SRC_DIR src)
set(LIB_INC_DIR inc)

file(GLOB LIB_SOURCES CONFIGURE_DEPENDS ${LIB_SRC_DIR}/*.cpp)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_INC_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${LIB_INC_DIR}/lint.hpp)

set(CMAKE_INSTALL_PREFIX "")

install(
        TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION inc/${PROJECT_NAME}
        )
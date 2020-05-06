cmake_minimum_required(VERSION 3.1)
project(violet LANGUAGES CXX)

option(VIOLET_BUILD_TESTS "Build the Violet tests" ON)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_library(${PROJECT_NAME} src/violet/hello.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

if (VIOLET_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

cmake_minimum_required(VERSION 3.1.2)
project(test_package LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(test_package test_package.cpp)

set_target_properties(test_package PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
)

target_link_libraries(test_package PRIVATE CONAN_PKG::violet)

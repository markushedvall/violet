cmake_minimum_required(VERSION 3.8)
project(test_package LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(test_package test_package.cpp)

target_compile_features(test_package PUBLIC cxx_std_17)

target_link_libraries(test_package PRIVATE CONAN_PKG::violet)

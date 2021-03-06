cmake_minimum_required(VERSION 3.14)
project(violet LANGUAGES CXX)

option(VIOLET_EXAMPLES "Build the violet examples" ON)
option(VIOLET_TEST "Build the Violet tests" ON)
option(VIOLET_FORMAT "Check the code format with clang-format" ${VIOLET_TEST})
option(VIOLET_LINT "Lint the code with clang-tidy" ${VIOLET_TEST})
option(VIOLET_WARNINGS_AS_ERRORS "All warnings will be treated as errors" OFF)
option(VIOLET_FIX "Try to fix format and lint problems" OFF)
option(VIOLET_COVERAGE "Build Violet with coverage" OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

if(NOT CONAN_EXPORTED)
  include(tools/cmake/conan.cmake)
  conan_cmake_run(
    CONANFILE conanfile.py
    GENERATORS cmake_find_package_multi
    BUILD missing
    NO_LOAD
  )
endif()

if(VIOLET_LINT)
  include(tools/cmake/lint.cmake)
else()
  function(violet_lint)
  endfunction()
endif()

add_library(violet
  src/violet/app_glfw.cpp
  src/violet/logger.cpp
)

target_compile_features(violet PUBLIC cxx_std_17)

find_package(glfw REQUIRED)
target_link_libraries(violet PUBLIC glfw::glfw)

target_include_directories(violet
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# Set compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(violet PUBLIC -Wall -pedantic -Wextra)
  if (VIOLET_WARNINGS_AS_ERRORS)
    target_compile_options(violet PUBLIC -Werror)
  endif()
  if(VIOLET_COVERAGE)
    target_compile_options(violet PUBLIC --coverage)
    target_link_options(violet PUBLIC --coverage)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  target_compile_options(violet PUBLIC /permissive /W4)
  if (VIOLET_WARNINGS_AS_ERRORS)
    target_compile_options(violet PUBLIC /WX)
  endif()
endif()

# Ignore missing PDB files for MSVC
target_link_options(violet PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>)

violet_lint(TARGET violet)

if(VIOLET_FORMAT)
  file(GLOB_RECURSE FORMAT_SOURCES CONFIGURE_DEPENDS
    include/*.h
    src/*.cpp
    src/*.h
    tests/*.cpp
    tests/*.h
    examples/*.cpp
    examples/*.h
  )
  include(tools/cmake/format.cmake)
  violet_format(TARGET violet SOURCES ${FORMAT_SOURCES})
endif()

if(VIOLET_TEST)
  enable_testing()
  add_subdirectory(tests)
endif()

if(VIOLET_EXAMPLES)
  add_subdirectory(examples)
endif()

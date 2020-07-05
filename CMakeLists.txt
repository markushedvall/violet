cmake_minimum_required(VERSION 3.12)
project(violet LANGUAGES CXX)

option(VIOLET_TEST "Build the Violet tests" ON)
option(VIOLET_FORMAT "Check the code format with clang-format" ${VIOLET_TEST})
option(VIOLET_LINT "Lint the code with clang-tidy" ${VIOLET_TEST})
option(VIOLET_WARNINGS_AS_ERRORS "All warnings will be treated as errors" OFF)
option(VIOLET_FIX "Try to fix format and lint problems" OFF)
option(VIOLET_COVERAGE "Build Violet with coverage" OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CONAN_EXPORTED)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
else()
  include(tools/cmake/conan.cmake)
  conan_cmake_run(
    CONANFILE conanfile.py
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing
  )
endif()

if(VIOLET_LINT)
  include(tools/cmake/lint.cmake)
else()
  function(violet_lint)
  endfunction()
endif()

add_library(violet
  src/violet/hello.cpp
)

target_compile_features(violet PUBLIC cxx_std_11)

target_include_directories(violet
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# Set compiler options
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(violet PUBLIC -Wall -pedantic -Wextra)
  if (VIOLET_WARNINGS_AS_ERRORS)
    target_compile_options(violet PUBLIC -Werror)
  endif()
  if(VIOLET_COVERAGE)
    target_compile_options(violet PUBLIC --coverage)
    target_link_options(violet PUBLIC --coverage)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(violet PUBLIC /permissive /W4)
  if (VIOLET_WARNINGS_AS_ERRORS)
    target_compile_options(violet PUBLIC /WX)
  endif()
endif()

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
  violet_format(SOURCES ${FORMAT_SOURCES})
endif()

if(VIOLET_TEST)
  enable_testing()
  add_subdirectory(tests)
endif()

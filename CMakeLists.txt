cmake_minimum_required(VERSION 3.1.2)
project(violet LANGUAGES CXX)

option(VIOLET_BUILD_TESTS "Build the Violet tests" ON)
option(VIOLET_CHECK_FORMAT "Check the code format with clang-format" ${VIOLET_BUILD_TESTS})
option(VIOLET_WARNINGS_AS_ERRORS "All warnings will be treated as errors" ${VIOLET_BUILD_TESTS})
option(VIOLET_BUILD_WITH_COVERAGE "Build Violet with coverage" OFF)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake)

include(conan)
conan_cmake_run(
  CONANFILE conanfile.py
  BASIC_SETUP CMAKE_TARGETS
  BUILD missing
)

add_library(violet
  src/violet/hello.cpp
)

set_target_properties(violet PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
)

target_include_directories(violet
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(violet PUBLIC -Wall -pedantic -Wextra)
  if (VIOLET_WARNINGS_AS_ERRORS)
    target_compile_options(violet PUBLIC -Werror)
  endif()
  if(VIOLET_BUILD_WITH_COVERAGE)
    target_compile_options(violet PUBLIC --coverage)
    target_link_options(violet PUBLIC --coverage)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(violet PUBLIC /permissive /W4)
  if (VIOLET_WARNINGS_AS_ERRORS)
    target_compile_options(violet PUBLIC /WX)
  endif()
endif()

file(GLOB_RECURSE FORMAT_SOURCES CONFIGURE_DEPENDS
  include/*.h
  src/*.cpp
  src/*.h
  tests/*.cpp
  tests/*.h
  examples/*.cpp
  examples/*.h
)

if(NOT CONAN_IN_LOCAL_CACHE)
  find_package(ClangFormat)
  if(CLANG_FORMAT_EXECUTABLE)
    add_custom_target(fix-format
      COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${FORMAT_SOURCES}
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
  endif()
endif()

if(VIOLET_CHECK_FORMAT)
  if (VIOLET_WARNINGS_AS_ERRORS)
    set(VIOLET_CHECK_FORMAT_WERROR -Werror)
  endif()
  find_package(ClangFormat REQUIRED)
  add_custom_target(check-format ALL
    COMMAND ${CLANG_FORMAT_EXECUTABLE} --dry-run ${VIOLET_CHECK_FORMAT_WERROR} ${FORMAT_SOURCES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
  add_dependencies(violet check-format)
endif()

if(VIOLET_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

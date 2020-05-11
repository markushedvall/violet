cmake_minimum_required(VERSION 3.1.2)
project(violet LANGUAGES CXX)

option(VIOLET_BUILD_TESTS "Build the Violet tests" ON)
option(VIOLET_CHECK_FORMAT "Check the code format with clang-format" ${VIOLET_BUILD_TESTS})

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake)

if(NOT CONAN_EXPORTED)
  include(conan)
  conan_cmake_install(CONANFILE conanfile.py BUILD missing)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

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
  find_package(ClangFormat REQUIRED)
  add_custom_target(check-format ALL
    COMMAND ${CLANG_FORMAT_EXECUTABLE} --dry-run -Werror ${FORMAT_SOURCES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
  add_dependencies(violet check-format)
endif()

if(VIOLET_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

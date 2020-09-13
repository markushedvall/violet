add_executable(violet_test
  main.cpp
  ${PROJECT_SOURCE_DIR}/src/violet/hello.test.cpp
)

find_package(Catch2 CONFIG REQUIRED)

target_link_libraries(violet_test PRIVATE violet Catch2::Catch2)
target_include_directories(violet_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

violet_lint(TARGET violet_test)

include(${CMAKE_BINARY_DIR}/Catch.cmake)
catch_discover_tests(violet_test)

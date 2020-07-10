add_executable(violet_test
  main.cpp
  ${PROJECT_SOURCE_DIR}/src/violet/hello.test.cpp
)

find_package(catch2 CONFIG REQUIRED)

target_link_libraries(violet_test PRIVATE violet Catch2::Catch2)

violet_lint(TARGET violet_test)

include(${CMAKE_BINARY_DIR}/Catch.cmake)
catch_discover_tests(violet_test)

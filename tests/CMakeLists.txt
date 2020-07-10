add_executable(violet_test
  main.cpp
  ${PROJECT_SOURCE_DIR}/src/violet/hello.test.cpp
)

target_link_libraries(violet_test PRIVATE violet CONAN_PKG::catch2)

violet_lint(TARGET violet_test)

include(${CMAKE_BINARY_DIR}/Catch.cmake)
catch_discover_tests(violet_test)

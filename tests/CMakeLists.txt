add_executable(violet_test
  main.cpp
  ${PROJECT_SOURCE_DIR}/src/violet/hello.test.cpp
)

set_target_properties(violet_test PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
)

target_link_libraries(violet_test PRIVATE ${PROJECT_NAME} CONAN_PKG::doctest)

include(${CMAKE_BINARY_DIR}/doctest.cmake)
doctest_discover_tests(violet_test)

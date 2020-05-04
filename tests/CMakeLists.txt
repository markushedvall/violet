add_executable(${PROJECT_NAME}-test main.cpp ${CMAKE_SOURCE_DIR}/src/violet/hello.test.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME} CONAN_PKG::doctest)

include(${CMAKE_BINARY_DIR}/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME}-test)

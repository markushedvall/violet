add_executable(violet_test
  main.cpp
  ${PROJECT_SOURCE_DIR}/src/violet/app.test.cpp
  ${PROJECT_SOURCE_DIR}/src/violet/logger.test.cpp
)

find_package(Catch2 CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(
  trompeloeil
  GIT_REPOSITORY https://github.com/rollbear/trompeloeil
  GIT_TAG v38
)
FetchContent_MakeAvailable(trompeloeil)

target_link_libraries(violet_test PRIVATE violet Catch2::Catch2 trompeloeil)
target_include_directories(violet_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

include(${CMAKE_BINARY_DIR}/Catch.cmake)
catch_discover_tests(violet_test)

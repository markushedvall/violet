add_executable(hello_world hello_world.cpp)

set_target_properties(violet_test PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
)

target_link_libraries(hello_world violet)

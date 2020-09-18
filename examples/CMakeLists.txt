add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world PRIVATE violet)
violet_lint(TARGET hello_world)

# Ignore missing PDB files
target_link_options(hello_world PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/ignore:4099>)

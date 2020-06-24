#include <catch2/catch.hpp>

#include <violet/violet.h>

namespace {

TEST_CASE("hello() should return hello world string") {
  REQUIRE(violet::hello() == "Hello, World!");
}

} // namespace

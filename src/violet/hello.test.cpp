#include <doctest/doctest.h>

#include <violet/violet.h>

namespace {

TEST_CASE("hello() should return hello world string") {
  CHECK(violet::hello() == "Hello, World!");
}

} // namespace

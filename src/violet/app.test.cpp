#include <violet/app.h>

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <iostream>
#include <memory>

namespace {

using violet::App;
using violet::TickResult;

class AppMock {
public:
  MAKE_MOCK0(tick, TickResult());
  virtual ~AppMock() {}
};

class TestApp : public App {
public:
  TickResult tick() override {
    return mock->tick();
  }

  std::unique_ptr<AppMock> mock;
};

TEST_CASE("App can run being constructed, ticked and destructed", "[App]") {
  auto owner = std::make_unique<trompeloeil::deathwatched<AppMock>>();
  auto mock = owner.get();

  trompeloeil::sequence seq{};

  REQUIRE_CALL(*mock, tick()).RETURN(TickResult::ok).IN_SEQUENCE(seq);
  REQUIRE_CALL(*mock, tick()).RETURN(TickResult::terminate).IN_SEQUENCE(seq);
  REQUIRE_DESTRUCTION(*mock).IN_SEQUENCE(seq);

  violet::run_app(
      [&]() {
        auto app = std::make_unique<TestApp>();
        app->mock = std::move(owner);
        return app;
      },
      [](auto, auto) {});
}

} // namespace

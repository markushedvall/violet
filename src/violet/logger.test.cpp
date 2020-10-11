#include "logger.h"

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

namespace {

using violet::Logger;
using violet::LogLevel;

class LogMock {
public:
  MAKE_MOCK2(log, void(LogLevel, const char*));
};

TEST_CASE("Logger can log with log function", "[Logger]") {
  LogMock mock{};
  Logger::set_log_function([&](auto l, auto m) { mock.log(l, m); });
  const char* msg{"log message"};

  SECTION("trace() logs with trace log level") {
    REQUIRE_CALL(mock, log(LogLevel::trace, msg));
    Logger::trace(msg);
  }
  SECTION("debug() logs with debug log level") {
    REQUIRE_CALL(mock, log(LogLevel::debug, msg));
    Logger::debug(msg);
  }
  SECTION("info() logs with information log level") {
    REQUIRE_CALL(mock, log(LogLevel::information, msg));
    Logger::info(msg);
  }
  SECTION("warn() logs with warning log level") {
    REQUIRE_CALL(mock, log(LogLevel::warning, msg));
    Logger::warn(msg);
  }
  SECTION("err() logs with error log level") {
    REQUIRE_CALL(mock, log(LogLevel::error, msg));
    Logger::err(msg);
  }
  SECTION("critical() logs with critical log level") {
    REQUIRE_CALL(mock, log(LogLevel::critical, msg));
    Logger::critical(msg);
  }
}

} // namespace

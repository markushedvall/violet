#include <violet/violet.h>

#include <iostream>

namespace {

using violet::App;
using violet::LogLevel;
using violet::TickResult;

class TestPackage final : public App {
public:
  TickResult tick() override {
    std::cout << "Tick! Terminating..." << std::endl;
    return TickResult::terminate;
  }
};

void onLog(LogLevel level, const char* msg) {
  if (level >= LogLevel::error) {
    std::cout << msg << std::endl;
  }
}

} // namespace

int main() {
  violet::run_app(violet::AppFactory<TestPackage>(), onLog);
}

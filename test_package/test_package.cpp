#include <iostream>

#include <violet/violet.h>

namespace {

using violet::App;
using violet::LogLevel;

class TestPackage final : public App {
public:
  void tick() override {
    std::cout << "Tick! Exiting..." << std::endl;
    exit(0);
  }
};

void onLog(LogLevel level, const char* msg) {
  if (level >= LogLevel::error) {
    std::cout << msg << std::endl;
  }
}

} // namespace

violet::AppConf violet::config() {
  return {violet::AppFactory<TestPackage>(), onLog};
}

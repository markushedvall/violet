#include <iostream>

#include <violet/violet.h>

namespace {

using violet::App;
using violet::LogLevel;

class HelloWorld final : public App {
public:
  HelloWorld() {
    std::cout << "Hello, World!" << std::endl;
  }

  void tick() override {
    // Do nothing
  }
};

void onLog(LogLevel level, const char* msg) {
  if (level >= LogLevel::error) {
    std::cout << msg << std::endl;
  }
}

} // namespace

violet::AppConf violet::config() {
  return {violet::AppFactory<HelloWorld>(), onLog};
}

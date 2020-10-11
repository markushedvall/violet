#include <violet/violet.h>

#include <iostream>

namespace {

using violet::App;
using violet::LogLevel;

class HelloWorld final : public App {
public:
  HelloWorld() {
    std::cout << "Hello, World!" << std::endl;
  }
};

void onLog(LogLevel level, const char* msg) {
  if (level >= LogLevel::error) {
    std::cout << msg << std::endl;
  }
}

} // namespace

VIOLET_RUN_APP(HelloWorld, onLog)

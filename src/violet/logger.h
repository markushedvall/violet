#ifndef VIOLET_LOGGER_H
#define VIOLET_LOGGER_H

#include <violet/log.h>

#include <functional>

namespace violet {

class Logger final {
public:
  static void set_log_function(const LogFunction& log_func);

  static void trace(const char* msg) {
    log_func_(LogLevel::trace, msg);
  }

  static void debug(const char* msg) {
    log_func_(LogLevel::debug, msg);
  }

  static void info(const char* msg) {
    log_func_(LogLevel::information, msg);
  }

  static void warn(const char* msg) {
    log_func_(LogLevel::warning, msg);
  }

  static void err(const char* msg) {
    log_func_(LogLevel::error, msg);
  }

  static void critical(const char* msg) {
    log_func_(LogLevel::critical, msg);
  }

  Logger() = delete;

private:
  static LogFunction log_func_;
};

} // namespace violet

#endif

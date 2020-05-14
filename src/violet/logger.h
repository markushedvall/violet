#ifndef VIOLET_LOGGER_H
#define VIOLET_LOGGER_H

#include <violet/log.h>

#include <functional>

namespace violet {

class Logger final {
public:
  static void init(const LogFunction& log_func);

  static void trace(const char* msg);

  static void debug(const char* msg);

  static void info(const char* msg);

  static void warn(const char* msg);

  static void err(const char* msg);

  static void critical(const char* msg);

  Logger() = delete;

private:
  static LogFunction log_func_;
};

} // namespace violet

#endif

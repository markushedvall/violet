#ifndef VIOLET_LOG_H
#define VIOLET_LOG_H

#include <functional>

namespace violet {

enum class LogLevel {
  trace = 0,
  debug = 1,
  information = 2,
  warning = 3,
  error = 4,
  critical = 5,
  none = 6,
};

using LogFunction = std::function<void(LogLevel, const char*)>;

} // namespace violet

#endif

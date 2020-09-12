#include <violet/logger.h>

namespace violet {

LogFunction Logger::log_func_{};

void Logger::set_log_function(const LogFunction& log_func) {
  log_func_ = log_func;
}

} // namespace violet

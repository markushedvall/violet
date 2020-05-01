#include <violet/logger.h>

namespace violet {

LogFunction Logger::log_func_{};

void Logger::init(const LogFunction& log_func) {
  log_func_ = log_func;
}

void Logger::trace(const char* msg) {
  log_func_(LogLevel::trace, msg);
}

void Logger::debug(const char* msg) {
  log_func_(LogLevel::debug, msg);
}

void Logger::info(const char* msg) {
  log_func_(LogLevel::information, msg);
}

void Logger::warn(const char* msg) {
  log_func_(LogLevel::warning, msg);
}

void Logger::err(const char* msg) {
  log_func_(LogLevel::error, msg);
}

void Logger::critical(const char* msg) {
  log_func_(LogLevel::critical, msg);
}

}

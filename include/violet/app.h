#ifndef VIOLET_APP_H
#define VIOLET_APP_H

#include <violet/log.h>

#include <functional>
#include <memory>
#include <type_traits>

namespace violet {

enum class TickResult {
  ok,
  terminate,
};

class App {
public:
  virtual TickResult tick() {
    return TickResult::ok;
  };
  virtual ~App() = default;

protected:
  App() = default;
  App(const App&) = default;
  App& operator=(const App&) = default;
  App(App&&) = default;
  App& operator=(App&&) = default;
};

using CreateAppFunction = std::function<std::unique_ptr<App>()>;

void run_app(const CreateAppFunction& create_app_function, const LogFunction& log_function);

template<typename T>
class AppFactory {
public:
  std::unique_ptr<App> operator()() const {
    static_assert(std::is_default_constructible<T>::value, "T must be default constructible");
    return std::unique_ptr<T>(new T());
  }
};

} // namespace violet

// NOLINTNEXTLINE - cppcoreguidelines-macro-usage
#define VIOLET_RUN_APP(APP, LOG_FUNCTION) \
  int main() { \
    violet::run_app(violet::AppFactory<APP>(), LOG_FUNCTION); \
  }

#endif

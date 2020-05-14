#ifndef VIOLET_APP_H
#define VIOLET_APP_H

#include <violet/log.h>

#include <functional>
#include <memory>
#include <type_traits>

namespace violet {

class App {
public:
  virtual void tick() = 0;
  virtual ~App() {}

protected:
  App() = default;
};

struct AppConf {
  std::function<std::unique_ptr<App>()> app;
  LogFunction log;
};

template<typename T>
class AppFactory {
public:
  std::unique_ptr<App> operator()() const {
    static_assert(std::is_default_constructible<T>::value, "T must be default constructible");
    return std::unique_ptr<T>(new T());
  }
};

AppConf config();

} // namespace violet

#endif

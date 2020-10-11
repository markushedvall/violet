#include <violet/app.h>
#include <violet/logger.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace violet {

static constexpr int default_width = 640;
static constexpr int default_height = 480;

class Glfw final {
public:
  Glfw() noexcept : initilized_(glfwInit() == GLFW_TRUE){};

  ~Glfw() {
    glfwTerminate();
  }

  explicit operator bool() const noexcept {
    return initilized_;
  }

  Glfw(const Glfw& other) = delete;
  Glfw(Glfw&& other) = delete;
  Glfw& operator=(const Glfw& other) = delete;
  Glfw& operator=(Glfw&& other) = delete;

private:
  bool initilized_;
};

class GlfwWindowDeleter final {
public:
  void operator()(GLFWwindow* window) {
    glfwDestroyWindow(window);
  }
};

using GlfwWindow = std::unique_ptr<GLFWwindow, GlfwWindowDeleter>;

void run_app(const CreateAppFunction& create_app_function, const LogFunction& log_function) {
  Logger::set_log_function(log_function);

  glfwSetErrorCallback([](int /*err*/, const char* msg) { Logger::err(msg); });

  Logger::trace("Initializing GLFW");
  Glfw glfw{};
  if (!glfw) {
    return;
  }

  Logger::trace("Creating window");
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GlfwWindow window{glfwCreateWindow(default_width, default_height, "", nullptr, nullptr)};
  if (!window) {
    return;
  }

  Logger::trace("Creating application");
  auto app = create_app_function();

  Logger::trace("Entering main loop");
  auto tick_result{TickResult::ok};
  while (glfwWindowShouldClose(window.get()) == GLFW_FALSE && tick_result == TickResult::ok) {
    tick_result = app->tick();
    glfwPollEvents();
  }
  Logger::trace("Leaving main loop");
}

} // namespace violet

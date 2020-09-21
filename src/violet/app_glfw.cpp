#include <violet/app.h>
#include <violet/logger.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace violet {

static constexpr int default_width = 640;
static constexpr int default_height = 480;

void run_app(const CreateAppFunction& create_app_function, const LogFunction& log_function) {
  Logger::set_log_function(log_function);

  glfwSetErrorCallback([](int /*err*/, const char* msg) { Logger::err(msg); });

  Logger::trace("Initializing GLFW");
  auto initialized = glfwInit();
  if (initialized == GLFW_FALSE) {
    return;
  }

  Logger::trace("Creating window");
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  auto* window = glfwCreateWindow(default_width, default_height, "", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    return;
  }

  {
    Logger::trace("Creating application");
    auto app = create_app_function();

    Logger::trace("Entering main loop");
    auto tick_result{TickResult::ok};
    while (glfwWindowShouldClose(window) == GLFW_FALSE && tick_result == TickResult::ok) {
      tick_result = app->tick();
      glfwPollEvents();
    }
  }

  Logger::trace("Destroying window");
  glfwDestroyWindow(window);

  Logger::trace("Terminating GLFW");
  glfwTerminate();
}

} // namespace violet

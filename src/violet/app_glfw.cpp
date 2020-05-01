#include <violet/app.h>
#include <violet/logger.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdlib>

using violet::Logger;

int main() {
  auto config = violet::config();
  Logger::init(config.log);

  glfwSetErrorCallback([](int err, const char* msg) { Logger::err(msg); });

  Logger::trace("Initializing GLFW");
  auto initialized = glfwInit();
  if (!initialized) {
    return EXIT_FAILURE;
  }

  Logger::trace("Creating window");
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  auto window = glfwCreateWindow(640, 480, "", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  {
    Logger::trace("Creating application");
    auto app = config.app();

    Logger::trace("Entering main loop");
    while (!glfwWindowShouldClose(window)) {
      app->tick();
      glfwPollEvents();
    }
  }

  Logger::trace("Destroying window");
  glfwDestroyWindow(window);

  Logger::trace("Terminating GLFW");
  glfwTerminate();

  return EXIT_SUCCESS;
}

#pragma once

#include <string>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

/**
 * Compatibility macro for `VK_MAKE_API_VERSION` if it is not defined.
 *
 * This just uses `VK_MAKE_VERSION` and ignores the variant parameter.
 */
#ifndef VK_MAKE_API_VERSION
#define VK_MAKE_API_VERSION(variant, major, minor, patch) \
  VK_MAKE_VERSION(major, minor, patch)
#endif  // VK_MAKE_API_VERSION

class Window {
  public:
    bool init(unsigned int width, unsigned int height, std::string title);
    bool initVulkan();
    void mainLoop();
    void cleanup();

  private:
    GLFWwindow *mWindow = nullptr;
    std::string mApplicationName;

    // must zero-initialize?
    VkInstance mInstance{};
    VkSurfaceKHR mSurface{};
};

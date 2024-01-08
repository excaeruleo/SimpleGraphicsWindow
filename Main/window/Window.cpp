#include <vector>

#include "Window.h"
#include "Logger.h"

bool Window::init(unsigned int width, unsigned int height, std::string title) {
  if (!glfwInit()) {
    Logger::log(1, "%s: glfwInit() error\n", __func__);
    return false;
  }
  if (!glfwVulkanSupported()) {
    glfwTerminate();
    Logger::log(1, "%s: Vulkan is not supported\n", __func__);
    return false;
  }

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  // require GLFW_NO_API for Vulkan usage
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!mWindow) {
    Logger::log(1, "%s: Could not create window\n", __func__);
    glfwTerminate();
    return false;
  }

  if (!initVulkan()) {
    Logger::log(1, "%s: Could not init Vulkan\n", __func__);
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(mWindow);

  Logger::log(1, "%s: Window successfully initialized\n", __func__);
  return true;
}

bool Window::initVulkan() {
  // pointer to glfwGetError error message
  const char* err_msg;

  VkResult result = VK_ERROR_UNKNOWN;

  VkApplicationInfo mAppInfo{};
  mAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  mAppInfo.pNext = nullptr;
  mAppInfo.pApplicationName = mApplicationName.c_str();
  mAppInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 0, 1);
  mAppInfo.pEngineName = "Game Animations Programming";
  mAppInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
  mAppInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 1, 0);

  uint32_t extensionCount = 0;
  const char** extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

  if (extensionCount == 0) {
    Logger::log(1, "%s error: no Vulkan extensions found\n", __func__);
    return false;
  }

  VkInstanceCreateInfo mCreateInfo{};
  mCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  mCreateInfo.pNext = nullptr;
  mCreateInfo.pApplicationInfo = &mAppInfo;
  mCreateInfo.enabledExtensionCount = extensionCount;
  mCreateInfo.ppEnabledExtensionNames = extensions;
  mCreateInfo.enabledLayerCount = 0;

  result = vkCreateInstance(&mCreateInfo, nullptr, &mInstance);
  if (result != VK_SUCCESS) {
    glfwGetError(&err_msg);
    Logger::log(1, "%s: Could not create Instance (%i): %s\n", __func__, result, err_msg);
    return false;
  }

  uint32_t physicalDeviceCount = 0;
  vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, nullptr);

  if (physicalDeviceCount == 0) {
    glfwGetError(&err_msg);
    Logger::log(1, "%s: No Vulkan capable GPU found: %s\n", __func__, err_msg);
    return false;
  }

  std::vector<VkPhysicalDevice> devices;
  vkEnumeratePhysicalDevices(mInstance, &physicalDeviceCount, devices.data());

  Logger::log(1, "%s: Found %u physical device(s):\n", __func__, physicalDeviceCount);

  result= glfwCreateWindowSurface(mInstance, mWindow, nullptr, &mSurface);
  if (result != VK_SUCCESS) {
    glfwGetError(&err_msg);
    Logger::log(1, "%s: Could not create Vulkan surface: %s\n", __func__, err_msg);
    return false;
  }

  return true;
}

void Window::mainLoop() {
  glfwSwapInterval(1);
  float color = 0.0f;
  while (!glfwWindowShouldClose(mWindow)) {
    color >= 1.0f ? color = 0.0f : color += 0.01f;
    glClearColor(color, color, color, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
  }
}

void Window::cleanup() {
  Logger::log(1, "%s: Terminating Window\n", __func__);
  vkDestroySurfaceKHR(mInstance, mSurface, nullptr);
  vkDestroyInstance(mInstance, nullptr);
  glfwDestroyWindow(mWindow);
  glfwTerminate();
}

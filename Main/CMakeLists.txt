cmake_minimum_required(VERSION 3.19)

project(
    glfw-demo
    VERSION 0.1.0
    DESCRIPTION "GLFW3 demo with OpenGL and Vulkan"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
endif()

project(Main)

file(GLOB SOURCES
    Main.cpp
    window/*.cpp
    tools/*.cpp
)
add_executable(Main ${SOURCES})

find_package(glfw3 3.3 REQUIRED)
find_package(Vulkan REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

if(UNIX)
    set(GLFW3_LIBRARY glfw)
    message(STATUS "GLFW3_LIBRARY: ${GLFW3_LIBRARY}")
endif()

include_directories(${GLFW3_INCLUDE_DIR} window tools)

target_link_libraries(Main PRIVATE ${GLFW3_LIBRARY} OpenGL::GL)
target_link_libraries(Main PRIVATE ${GLFW3_LIBRARY} Vulkan::Vulkan)

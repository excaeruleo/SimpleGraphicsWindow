# SimpleGraphicsWindow
Simple Graphics Window using OpenGL and Vulkan API. Work in progress.

## How to Run the Project
Go to the build directory after forking the repo as a local version to your machine, run the command "cmake .." in the build directory to write the build files to the directory, then run the command "make" to build the target file Main, and then render the graphics window using the command "./Main". You should get a black graphics window, with additional output from Vulkan to the command line saying "initVulkan: 1 physical device(s)", and then after exiting out of the graphics window by pressing on the x at the top right of the graphics window, the two lines "init: Window successfully initiated" and "cleanup: Terminating Window" should output as well.

#include <memory>

#include "window/Window.h"
#include "tools/Logger.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<Window> w = std::make_unique<Window>();

    if (! w -> init(640, 480, "Test Window")) {
        Logger::log(1, "%s error: Window init error\n", __FUNCTION__);
        return -1;
    }
    w -> mainLoop();
    w -> cleanup();
    return 0;
}
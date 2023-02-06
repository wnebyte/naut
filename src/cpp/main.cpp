#include <cstdlib>
#include <string>
#include "core/window.h"

using namespace core;

int main(int argc, const char *argv[]) {
    Window* window = Window::newInstance("MyTitle");
    window->update(0);
    window->destroy();
    return EXIT_SUCCESS;
}

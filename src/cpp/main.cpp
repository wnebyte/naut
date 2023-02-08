#include <cstdlib>
#include "core/window.h"

using namespace core;

int main(int argc, const char *argv[]) {
    Window* window = Window::newInstance("Naut");
    float dt;
    float lastFrame = 0.0f;

    while (!window->shouldClose()) {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window->pollEvents(dt);
        window->update(dt);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        window->swapBuffers();
    }

    return EXIT_SUCCESS;
}

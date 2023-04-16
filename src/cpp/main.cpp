#include <cstdlib>
#include "core/window.h"
#include "core/mouselistener.h"
#include "core/keylistener.h"
#include "renderer/batchrenderer.h"
#include "renderer/primitives.h"

using namespace core;
using namespace renderer;

int main(int argc, char *argv[]) {
    Window* window = Window::newInstance("Naut");
    float dt;
    float lastFrame = 0.0f;

    while (!window->shouldClose()) {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        window->pollEvents(dt);
        window->update(dt);
        window->swapBuffers();

        MouseListener::endFrame();
        KeyListener::endFrame();
    }

    return EXIT_SUCCESS;
}

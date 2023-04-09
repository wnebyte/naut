#include <cstdlib>
#include <vector>
#include "core/window.h"
#include "core/mouselistener.h"
#include "core/keylistener.h"
#include "renderer/batchrenderer.h"
#include "renderer/box.h"
#include "renderer/renderer.h"
#include "renderer/primitives.h"

using namespace core;
using namespace renderer;

void test() {
    std::vector<BatchRenderer<Box>> boxes;
    std::vector<BatchRenderer<Vertex2>> vertices;
    std::vector<Renderer*> batches;

    for (auto& e : boxes) {
        batches.push_back(&e);
    }

    BatchRenderer<Vertex2> batch = vertices[0];
    batch.add(Vertex2{{}, {}, {}, 0});
}

int main(int argc, const char *argv[]) {
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

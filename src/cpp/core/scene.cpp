#include "core/scene.h"
#include "core/window.h"
#include "core/camera.h"
#include "core/perspectivecamera.h"
#include "io/keylistener.h"

namespace core {

    using namespace io::keylistener;

    static const glm::vec4 position{0.0f};

    static const float zNear = 0.1f;

    static const float zFar = 10000;

    static const float debounceTime = 2.0f;

    static float debounce = debounceTime;

    static PerspectiveCamera perspective{position, zNear, zFar, 1980.0f / 1080.0f};

    Scene::Scene(Window* window)
            : window(window), camera(&perspective) {}

    Scene::~Scene() noexcept {
        try {
            // do nothing
        } catch ( ... ) {}
    }

    void Scene::update(float dt) {
        debounce -= dt;
        camera->update(dt);

        if (debounce <= 0) {
            debounce = debounceTime;
        }
    }

    void Scene::processInput(float dt) {
        if (isKeyPressed(GLFW_KEY_ESCAPE)) {
            window->setShouldClose(true);
            return;
        }
        if (isKeyDown(GLFW_KEY_W)) {
            camera->handleKeyboard(Camera::Direction::Forward, dt);
        }
        if (isKeyDown(GLFW_KEY_S)) {
            camera->handleKeyboard(Camera::Direction::Backward, dt);
        }
        if (isKeyDown(GLFW_KEY_A)) {
            camera->handleKeyboard(Camera::Direction::Left, dt);
        }
        if (isKeyDown(GLFW_KEY_D)) {
            camera->handleKeyboard(Camera::Direction::Right, dt);
        }
        if (isKeyDown(GLFW_KEY_SPACE)) {
            camera->handleKeyboard(Camera::Direction::Up, dt);
        }
        if (isKeyDown(GLFW_KEY_LEFT_CONTROL)) {
            camera->handleKeyboard(Camera::Direction::Down, dt);
        }
    }

    Window* Scene::getWindow() const noexcept {
        return window;
    }

    std::shared_ptr<Camera> Scene::getCamera() const noexcept {
        return camera;
    }
}

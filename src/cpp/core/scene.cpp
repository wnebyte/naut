#include <iostream>
#include "core/scene.h"
#include "core/window.h"
#include "core/keylistener.h"
#include "core/camera.h"
#include "core/perspectivecamera.h"
#include "renderer/shader.h"
#include "renderer/batchrenderer.h"
#include "utility/colors.h"

namespace core {

    using namespace renderer;

    static const std::string vertexPath{"assets/shaders/vertex/vertex2D.glsl"};

    static const std::string fragmentPath{"assets/shaders/fragment/vertex2D.glsl"};

    static const glm::vec4 position{0.0f};

    static const float zNear = 0.1f;

    static const float zFar = 10000;

    static const float debounceTime = 2.0f;

    static float debounce = debounceTime;

    static PerspectiveCamera perspective{position, zNear, zFar, 1980.0f / 1080.0f};

    Scene::Scene(Window* window)
    : camera(&perspective),
      shader(new Shader{vertexPath, fragmentPath}),
      window(window) {
        shader->compile();
    }

    Scene::~Scene() noexcept {
        try {
            delete camera;
            delete shader;
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
        if (KeyListener::isKeyBeginPressed(GLFW_KEY_ESCAPE)) {
            window->setShouldClose(true);
            return;
        }
        if (KeyListener::isKeyPressed(GLFW_KEY_W)) {
            camera->handleKeyboard(Camera::Movement::Forward, dt);
        }
        if (KeyListener::isKeyPressed(GLFW_KEY_S)) {
            camera->handleKeyboard(Camera::Movement::Backward, dt);
        }
        if (KeyListener::isKeyPressed(GLFW_KEY_A)) {
            camera->handleKeyboard(Camera::Movement::Left, dt);
        }
        if (KeyListener::isKeyPressed(GLFW_KEY_D)) {
            camera->handleKeyboard(Camera::Movement::Right, dt);
        }
        if (KeyListener::isKeyPressed(GLFW_KEY_SPACE)) {
            camera->handleKeyboard(Camera::Movement::Up, dt);
        }
        if (KeyListener::isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
            camera->handleKeyboard(Camera::Movement::Down, dt);
        }
    }

    Camera* Scene::getCamera() const noexcept {
        return camera;
    }
}

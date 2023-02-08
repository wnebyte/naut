#include "core/scene.h"
#include "core/camera.h"
#include "renderer/boxrenderer.h"
#include "utility/colors.h"

namespace core {

    using namespace renderer;

    static const Box box{glm::vec3{0.0f, 0.0f, -5.0f}, WHITE4};

    Scene::Scene()
    : camera(nullptr), renderer()
    {}

    Scene::~Scene() noexcept {
        try {
            delete camera;
        } catch ( ... ) {}
    }

    void Scene::update(float) {
        renderer.add(box);
        // render
    }

    void Scene::processInput(float) {

    }
}
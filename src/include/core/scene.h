#ifndef NAUT_SCENE_H
#define NAUT_SCENE_H

#include "camerafwd.h"
#include "renderer/boxrenderer.h"

namespace core {
    class Scene {
    public:
        Scene();

        ~Scene() noexcept;

        void update(float);

        void processInput(float);

    private:
        Camera* camera;
        renderer::BoxRenderer renderer;
    };
}

#endif //NAUT_SCENE_H

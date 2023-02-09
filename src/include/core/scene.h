#ifndef NAUT_SCENE_H
#define NAUT_SCENE_H

#include "windowfwd.h"
#include "scenefwd.h"
#include "camerafwd.h"
#include "renderer/shaderfwd.h"
#include "renderer/boxrenderer.h"

namespace core {

    using namespace renderer;

    class Scene {
    public:
        Scene(Window*);

        ~Scene() noexcept;

        Scene(const Scene&) = delete;

        Scene& operator=(const Scene&) = delete;

        Scene(Scene&&) = delete;

        Scene& operator=(Scene&&) = delete;

        void update(float);

        void processInput(float);

        Camera* getCamera() const noexcept;

    private:
        Window* window;
        Camera* camera;
        Shader* shader;
        BoxRenderer renderer;
    };
}

#endif //NAUT_SCENE_H

#ifndef NAUT_SCENE_H
#define NAUT_SCENE_H

#include <memory>
#include "windowfwd.h"
#include "scenefwd.h"
#include "camerafwd.h"

namespace core {

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

        Window* getWindow() const noexcept;

        std::shared_ptr<Camera> getCamera() const noexcept;

    private:
        Window* window;
        std::shared_ptr<Camera> camera;
    };
}

#endif //NAUT_SCENE_H

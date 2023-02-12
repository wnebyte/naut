#ifndef NAUT_RENDERER_H
#define NAUT_RENDERER_H

#include "core/camerafwd.h"
#include "shaderfwd.h"

using Camera = core::Camera;

namespace renderer {
    class Renderer {
    public:
        virtual ~Renderer() = default;

        virtual void render(const Camera&, const Shader&) {}
    };
}

#endif //NAUT_RENDERER_H

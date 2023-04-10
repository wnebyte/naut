#ifndef NAUT_RENDERER_H
#define NAUT_RENDERER_H

#include "core/camerafwd.h"
#include "shaderfwd.h"

using Camera = core::Camera;

namespace renderer {
    class Renderer {
    public:
        Renderer() = default;

        virtual ~Renderer() = default;

        virtual void render() = 0;
    };
}

#endif //NAUT_RENDERER_H

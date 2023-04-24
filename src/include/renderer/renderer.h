#ifndef NAUT_RENDERER_H
#define NAUT_RENDERER_H

#include "rendererfwd.h"

namespace renderer {
    class Renderer {
    public:
        Renderer() = default;

        virtual ~Renderer() = default;

        virtual void render() = 0;
    };
}

#endif //NAUT_RENDERER_H

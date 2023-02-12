#ifndef NAUT_BOXRENDERER_H
#define NAUT_BOXRENDERER_H

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "core/camerafwd.h"
#include "shaderfwd.h"

typedef uint32_t uint;

namespace renderer {
    struct Box;

    class BoxRenderer {
    public:
        BoxRenderer();

        ~BoxRenderer() noexcept;

        void init();

        void render(const core::Camera* const, const Shader&);

        bool add(const Box&);

        std::size_t size() const noexcept;

    private:
        struct Vertex;

        uint vao;
        uint vbo;
        std::size_t sz;
        bool initialized;
        Vertex* data;

        void tesselate(const Box& box);
    };
}

#endif //NAUT_BOXRENDERER_H

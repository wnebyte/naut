#ifndef NAUT_BOXRENDERER_H
#define NAUT_BOXRENDERER_H

#include <cstdint>
#include "core/camerafwd.h"
#include "shaderfwd.h"

typedef uint32_t uint;

namespace renderer {
    struct Box {
        glm::vec3 position;
        glm::vec4 color;
    };

    class BoxRenderer {
    public:
        BoxRenderer();

        ~BoxRenderer() noexcept;

        void start();

        void render(const core::Camera* const, const Shader&);

        bool add(const Box&);

        std::size_t size() const noexcept;

    private:
        struct Vertex {
            glm::vec3 position;
            glm::vec4 color;
        };

        uint vao;
        uint vbo;
        std::size_t sz;
        bool started;
        Vertex* data;

        void tesselate(const Box& box);
    };
}

#endif //NAUT_BOXRENDERER_H

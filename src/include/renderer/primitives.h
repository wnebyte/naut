#ifndef NAUT_PRIMITIVES_H
#define NAUT_PRIMITIVES_H

#include <initializer_list>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "primitivesfwd.h"
#include "vertexattribute.h"

namespace renderer {

    struct Line2 {
        class Tesselator {
        public:
            typedef Line2 Type;
            static std::initializer_list<VertexAttribute> attrs();
            static std::size_t size();

            Tesselator() = default;

            ~Tesselator() noexcept = default;

            void tesselate(const Line2&, size_t, Type*) const;
        };

        glm::vec2 position;
        glm::vec4 color;
    };

    struct Line3 {
        glm::vec3 position;
        glm::vec4 color;
    };

    struct Vertex2 {
        class Tesselator {
        public:
            typedef Vertex2 Type;
            static std::initializer_list<VertexAttribute> attrs();
            static std::size_t size();

            void tesselate(const Vertex2&, size_t, Type*) const;
        };

        glm::vec2 position;
        glm::vec4 color;
        glm::vec2 uv;
        int32_t texId;
    };

    struct Vertex3 {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    struct BoxVertex3 {
        glm::vec3 position;
        glm::vec4 color;
    };
}

#endif //NAUT_PRIMITIVES_H

#ifndef NAUT_BOX_H
#define NAUT_BOX_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <initializer_list>
#include "primitives.h"
#include "vertexattribute.h"

namespace renderer {
    struct Box {
        class Tesselator {
        public:
            typedef BoxVertex3 Type;
            static std::initializer_list<VertexAttribute> attrs();
            static std::size_t size();

            void tesselate(const Box&, std::size_t, Type data[]) const;
        };

        glm::vec3 position;
        glm::vec4 color;
    };
}

#endif //NAUT_BOX_H

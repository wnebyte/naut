#ifndef NAUT_PRIMITIVES_H
#define NAUT_PRIMITIVES_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "primitivesfwd.h"

namespace renderer {

    struct Line2D {
        glm::vec2 position;
    };

    struct Line3D {
        glm::vec3 position;
    };

    struct Vertex2D {
        glm::vec2 position;
        glm::vec2 uv;
    };

    struct Vertex3D {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };
}

#endif //NAUT_PRIMITIVES_H

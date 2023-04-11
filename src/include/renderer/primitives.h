#ifndef NAUT_PRIMITIVES_H
#define NAUT_PRIMITIVES_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "primitivesfwd.h"
#include "vertexattribute.h"

namespace renderer {

    struct gl_Line2 {
        glm::vec2 position;
        glm::vec4 color;
    };

    struct Line2 {
        glm::vec2 start;
        glm::vec2 end;
        glm::vec4 color;
        int32_t zIndex;
        float width;
    };

    struct gl_Line3 {
        glm::vec3 position;
        glm::vec4 color;
    };

    struct Line3 {
        glm::vec3 start;
        glm::vec3 end;
        glm::vec4 color;
        float width;
    };

    struct Vertex2 {
        glm::vec2 position;
        glm::vec4 color;
        glm::vec2 uv;
        int32_t texId;
        int32_t zIndex;
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

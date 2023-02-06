#ifndef NAUT_BOX_H
#define NAUT_BOX_H

#include <glm/vec3.hpp>
#include "material.h"

typedef uint32_t uint;

namespace renderer {
    struct Box {
        glm::vec3 position;
        glm::vec3 scale;
        Material top;
        Material bottom;
        Material right;
        Material left;
        Material front;
        Material back;
    };
}

#endif //NAUT_BOX_H

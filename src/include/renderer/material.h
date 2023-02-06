#ifndef NAUT_MATERIAL_H
#define NAUT_MATERIAL_H

#include <glm/vec3.hpp>

namespace renderer {
    struct Material {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
    };
}

#endif //NAUT_MATERIAL_H

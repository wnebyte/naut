#ifndef NAUT_CMATH_H
#define NAUT_CMATH_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace utility {

    class CMath {
    public:
        static void rotate(glm::vec2& vec, float angleDeg, const glm::vec2& origin);
    };
}

#endif //NAUT_CMATH_H

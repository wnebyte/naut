#ifndef NAUT_MATH_H
#define NAUT_MATH_H

#include "glm.h"

namespace utility {
    namespace math {
        void rotate(glm::vec2& vec, float angleDeg, const glm::vec2& origin);

        void rotate(glm::vec3& vec, float angleDeg, const glm::vec3& origin);
    }
}

#endif //NAUT_MATH_H

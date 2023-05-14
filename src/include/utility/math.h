#ifndef NAUT_MATH_H
#define NAUT_MATH_H

#include "glm.h"
#include "types.h"

namespace utility {
    namespace math {
        void rotate(glm::vec2& vec, f32_t angleDeg, const glm::vec2& origin);

        void rotate(glm::vec3& vec, f32_t angleDeg, const glm::vec3& origin);

        int32_t clamp(int32_t val, int32_t min, int32_t max);

        f32_t clamp(f32_t val, f32_t min, f32_t max);

        int32_t max(int32_t, int32_t);

        int32_t max3(int32_t, int32_t, int32_t);

        int32_t min(int32_t, int32_t);

        int32_t min3(int32_t, int32_t, int32_t);

        f32_t max(f32_t, f32_t);

        f32_t max3(f32_t, f32_t, f32_t);

        f32_t min(f32_t, f32_t);

        f32_t min3(f32_t, f32_t, f32_t);
    }
}

#endif //NAUT_MATH_H

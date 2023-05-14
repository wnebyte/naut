#include "utility/math.h"

namespace utility {

    namespace math {

        void rotate(glm::vec2& vec, float angleDeg, const glm::vec2& origin) {
            float angleRadians = glm::radians(angleDeg);
            float cos = glm::cos(angleRadians);
            float sin = glm::sin(angleRadians);

            float dx = vec.x - origin.x;
            float dy = vec.y - origin.y;

            vec.x = ((dx * cos) - (dy * sin) + origin.x);
            vec.y = ((dx * sin) - (dy * cos) + origin.y);
        }

        void rotate(glm::vec3& vec, float angleDeg, const glm::vec3& origin) {
            glm::vec2 vec_tmp{vec};
            const glm::vec2 origin_tmp{origin};

            rotate(vec_tmp, angleDeg, origin_tmp);

            vec.x = vec_tmp.x;
            vec.y = vec_tmp.y;
        }

        int32_t clamp(int32_t val, int32_t min, int32_t max) {
            if (val < min) return min;
            else if (val > max) return max;
            else return val;
        }

        f32_t clamp(f32_t val, f32_t min, f32_t max) {
            if (val < min) return min;
            else if (val > max) return max;
            else return val;
        }

        int32_t max(int32_t i1, int32_t i2) {
            return (i1 >= i2) ? i1 : i2;
        }

        int32_t max3(int32_t i1, int32_t i2, int32_t i3) {
            return max(max(i1, i2), i3);
        }

        int32_t min(int32_t i1, int32_t i2) {
            return (i2 < i1) ? i2 : i1;
        }

        int32_t min3(int32_t i1, int32_t i2, int32_t i3) {
            return min(min(i1, i2), i3);
        }

        f32_t max(f32_t f1, f32_t f2) {
            return (f1 >= f2) ? f1 : f2;
        }

        f32_t max3(f32_t f1, f32_t f2, f32_t f3) {
            return max(max(f1, f2), f3);
        }

        f32_t min(f32_t f1, f32_t f2) {
            return (f2 < f1) ? f2 : f1;
        }

        f32_t min3(f32_t f1, f32_t f2, f32_t f3) {
            return min(min(f1, f2), f3);
        }
    }
}

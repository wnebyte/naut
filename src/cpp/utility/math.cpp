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
    }
}

#include <glm/common.hpp>
#include <glm/trigonometric.hpp>
#include "utility/cmath.h"

namespace utility {

    void CMath::rotate(glm::vec2& vec, float angleDeg, const glm::vec2& origin) {
        float angleRadians = glm::radians(angleDeg);
        float cos = glm::cos(angleRadians);
        float sin = glm::sin(angleRadians);

        float dx = vec.x - origin.x;
        float dy = vec.y - origin.y;

        float xPrime = (dx * cos) - (dy * sin);
        float yPrime = (dx * sin) - (dy * cos);

        xPrime += origin.x;
        yPrime += origin.y;

        vec.x = xPrime;
        vec.y = yPrime;
    }
}


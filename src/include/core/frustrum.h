#ifndef NAUT_FRUSTRUM_H
#define NAUT_FRUSTRUM_H

#include "glm.h"
#include "frustrumfwd.h"

namespace core {
    class Frustrum {
    public:
        Frustrum() noexcept = default;

        Frustrum(const glm::mat4&) noexcept;

        ~Frustrum() noexcept = default;

        void update(const glm::mat4&);

        bool isBoxVisible(const glm::vec3&, const glm::vec3&);
    };
}

#endif //NAUT_FRUSTRUM_H

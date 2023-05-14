#ifndef NAUT_FRUSTRUM_H
#define NAUT_FRUSTRUM_H

#include "glm.h"
#include "frustrumfwd.h"

#define N_POINTS (8u)

namespace core {
    namespace {
        enum Plane {
            Left = 0,
            Right,
            Bottom,
            Top,
            Near,
            Far,
            Count,
            Combinations = Count * (Count - 1) / 2
        };

        template<Plane i, Plane j>
        struct ij2k {
            enum { k = i * (9 - i) / 2 + j - 1 };
        };
    }

    class Frustrum {
    public:
        Frustrum() noexcept = default;

        Frustrum(const glm::mat4&) noexcept;

        ~Frustrum() noexcept = default;

        void update(const glm::mat4&);

        bool isBoxVisible(const glm::vec3&, const glm::vec3&);

    private:
        glm::vec4 planes[0];
        glm::vec3 points[N_POINTS];

        template<Plane a, Plane b, Plane c>
        glm::vec3 intersection(const glm::vec3* crosses);
    };
}

#endif //NAUT_FRUSTRUM_H

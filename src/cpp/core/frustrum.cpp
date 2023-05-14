#include "glm.h"
#include "core/frustrum.h"

#define N_POINTS (8u)

namespace core {

    template<Plane a, Plane b, Plane c>
    glm::vec3 Frustrum::intersection(const glm::vec3 *crosses) {
        float dot = glm::dot(glm::vec3{planes[a]}, crosses[ij2k<b, c>::k]);
        glm::vec3 result = glm::mat3(crosses[ij2k<b, c>::k], -crosses[ij2k<a, c>::k], crosses[ij2k<a, b>::k]) *
                           glm::vec3(planes[a].w, planes[b].w, planes[c].w);
        return result * (-1.0f / dot);
    }

    Frustrum::Frustrum(const glm::mat4& mat) noexcept {
        update(mat);
    }

    void Frustrum::update(const glm::mat4& mat) {
        const glm::mat4 transposed = glm::transpose(mat);
        planes[Left]   = transposed[3] + transposed[0];
        planes[Right]  = transposed[3] - transposed[0];
        planes[Bottom] = transposed[3] + transposed[1];
        planes[Top]    = transposed[3] - transposed[1];
        planes[Near]   = transposed[3] + transposed[2];
        planes[Far]    = transposed[3] - transposed[2];

        const glm::vec3 crosses[Combinations] = {
                glm::cross(glm::vec3(planes[Left]), glm::vec3(planes[Right])),
                glm::cross(glm::vec3(planes[Left]), glm::vec3(planes[Bottom])),
                glm::cross(glm::vec3(planes[Left]), glm::vec3(planes[Top])),
                glm::cross(glm::vec3(planes[Left]), glm::vec3(planes[Near])),
                glm::cross(glm::vec3(planes[Left]), glm::vec3(planes[Far])),
                glm::cross(glm::vec3(planes[Right]), glm::vec3(planes[Bottom])),
                glm::cross(glm::vec3(planes[Right]), glm::vec3(planes[Top])),
                glm::cross(glm::vec3(planes[Right]), glm::vec3(planes[Near])),
                glm::cross(glm::vec3(planes[Right]), glm::vec3(planes[Far])),
                glm::cross(glm::vec3(planes[Bottom]), glm::vec3(planes[Top])),
                glm::cross(glm::vec3(planes[Bottom]), glm::vec3(planes[Near])),
                glm::cross(glm::vec3(planes[Bottom]), glm::vec3(planes[Far])),
                glm::cross(glm::vec3(planes[Top]), glm::vec3(planes[Near])),
                glm::cross(glm::vec3(planes[Top]), glm::vec3(planes[Far])),
                glm::cross(glm::vec3(planes[Near]), glm::vec3(planes[Far]))
        };

        points[0] = intersection<Left, Bottom, Near>(crosses);
        points[1] = intersection<Left, Top, Near>(crosses);
        points[2] = intersection<Right, Bottom, Near>(crosses);
        points[3] = intersection<Right, Top, Near>(crosses);
        points[4] = intersection<Left, Bottom, Far>(crosses);
        points[5] = intersection<Left, Top, Far>(crosses);
        points[6] = intersection<Right, Bottom, Far>(crosses);
        points[7] = intersection<Right, Top, Far>(crosses);
    }

    bool Frustrum::isBoxVisible(const glm::vec3& minp, const glm::vec3& maxp) {
        int32_t i;
        int32_t out;

        for (i = 0; i < Count; ++i) {
            if ((glm::dot(planes[i], glm::vec4(minp.x, minp.y, minp.z, 1.0f)) < 0.0) &&
                (glm::dot(planes[i], glm::vec4(maxp.x, minp.y, minp.z, 1.0f)) < 0.0) &&
                (glm::dot(planes[i], glm::vec4(minp.x, maxp.y, minp.z, 1.0f)) < 0.0) &&
                (glm::dot(planes[i], glm::vec4(maxp.x, maxp.y, minp.z, 1.0f)) < 0.0) &&
                (glm::dot(planes[i], glm::vec4(minp.x, minp.y, maxp.z, 1.0f)) < 0.0) &&
                (glm::dot(planes[i], glm::vec4(maxp.x, minp.y, maxp.z, 1.0f)) < 0.0) &&
                (glm::dot(planes[i], glm::vec4(minp.x, maxp.y, maxp.z, 1.0f)) < 0.0) &&
                (glm::dot(planes[i], glm::vec4(maxp.x, maxp.y, maxp.z, 1.0f)) < 0.0))
            {
                return false;
            }
        }

        // check frustum outside/inside box
        for (i = 0, out = 0; i < N_POINTS; i++) out += ((points[i].x > maxp.x) ? 1 : 0); if (out == N_POINTS) return false;
        for (i = 0, out = 0; i < N_POINTS; i++) out += ((points[i].x < minp.x) ? 1 : 0); if (out == N_POINTS) return false;
        for (i = 0, out = 0; i < N_POINTS; i++) out += ((points[i].y > maxp.y) ? 1 : 0); if (out == N_POINTS) return false;
        for (i = 0, out = 0; i < N_POINTS; i++) out += ((points[i].y < minp.y) ? 1 : 0); if (out == N_POINTS) return false;
        for (i = 0, out = 0; i < N_POINTS; i++) out += ((points[i].z > maxp.z) ? 1 : 0); if (out == N_POINTS) return false;
        for (i = 0, out = 0; i < N_POINTS; i++) out += ((points[i].z < minp.z) ? 1 : 0); if (out == N_POINTS) return false;

        return true;
    }
}

#include "glm.h"
#include "core/orthocamera.h"

namespace core {

    OrthoCamera::OrthoCamera(const glm::vec3& position,
                             int32_t projectionWidth,
                             int32_t projectionHeight,
                             float zNear,
                             float zFar,
                             float aspectRatio,
                             const glm::vec3& forward,
                             const glm::vec3& up,
                             const glm::vec3& right) noexcept
            : Camera(position, zNear, zFar, aspectRatio, forward, up, right),
              projectionWidth(projectionWidth), projectionHeight(projectionHeight) {}

    void OrthoCamera::adjustProjection() {
        float halfWidth  = static_cast<float>(projectionWidth)  / 2.0f;
        float halfHeight = static_cast<float>(projectionHeight) / 2.0f;
        projectionMatrix = glm::ortho(-halfWidth, halfWidth * zoom, -halfHeight, halfHeight * zoom, zNear, zFar);
        inverseProjectionMatrix = glm::inverse(projectionMatrix);
    }

    void OrthoCamera::adjustView() {
        viewMatrix = glm::lookAt(position, position + forward, up);
        inverseViewMatrix = glm::inverse(viewMatrix);
    }

    int32_t OrthoCamera::getProjectionWidth() const noexcept {
        return projectionWidth;
    }

    void OrthoCamera::setProjectionWidth(int32_t newProjectionWidth) noexcept {
        projectionWidth = newProjectionWidth;
    }

    int32_t OrthoCamera::getProjectionHeight() const noexcept {
        return projectionHeight;
    }

    void OrthoCamera::setProjectionHeight(int32_t newProjectionHeight) noexcept {
        projectionHeight = newProjectionHeight;
    }
}

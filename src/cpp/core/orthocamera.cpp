#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "core/orthocamera.h"

namespace core {

    OrthoCamera::OrthoCamera(const glm::vec3& position,
                             int32_t projectionWidth,
                             int32_t projectionHeight,
                             float zNear,
                             float zFar,
                             float aspectRatio,
                             const glm::vec3& viewEye,
                             const glm::vec3& viewCenter,
                             const glm::vec3& viewUp) noexcept
    : Camera(position, zNear, zFar, aspectRatio),
      projectionWidth(projectionWidth), projectionHeight(projectionHeight),
      viewEye(viewEye), viewCenter(viewCenter), viewUp(viewUp) {}

    void OrthoCamera::adjustProjection() {
        float halfWidth  = static_cast<float>(projectionWidth)  / 2.0f;
        float halfHeight = static_cast<float>(projectionHeight) / 2.0f;
        projectionMatrix = glm::ortho(-halfWidth, halfWidth * zoom, -halfHeight, halfHeight * zoom, zNear, zFar);
        inverseProjectionMatrix = glm::inverse(projectionMatrix);
    }

    void OrthoCamera::adjustView() {
        viewMatrix = glm::lookAt(viewEye, viewCenter, viewUp);
        inverseViewMatrix = glm::inverse(viewMatrix);
    }

    int32_t OrthoCamera::getProjectionWidth() const noexcept {
        return projectionWidth;
    }

    void OrthoCamera::setProjectionWidth(int32_t newProjectionWidth) noexcept {
        projectionHeight = newProjectionWidth;
    }

    int32_t OrthoCamera::getProjectionHeight() const noexcept {
        return projectionHeight;
    }

    void OrthoCamera::setProjectionHeight(int32_t newProjectionWidth) noexcept {
        projectionWidth = newProjectionWidth;
    }

    glm::vec3 OrthoCamera::getViewEye() const noexcept {
        return viewEye;
    }

    void OrthoCamera::setViewEye(const glm::vec3& newViewEye) noexcept {
        viewEye = newViewEye;
    }

    glm::vec3 OrthoCamera::getViewCenter() const noexcept {
        return viewCenter;
    }

    void OrthoCamera::setViewCenter(const glm::vec3& newViewCenter) noexcept {
        viewCenter = newViewCenter;
    }

    glm::vec3 OrthoCamera::getViewUp() const noexcept {
        return viewUp;
    }

    void OrthoCamera::setViewUp(const glm::vec3& newViewUp) noexcept {
        viewUp = newViewUp;
    }
}

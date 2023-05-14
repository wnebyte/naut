#include <glm/ext/matrix_transform.hpp>
#include "core/camera.h"

#define DEFAULT_ZOOM (1.0f)

namespace core {

    Camera::Camera(const glm::vec3& position,
                   float zNear, float zFar, float aspectRatio,
                   const glm::vec3& forward,
                   const glm::vec3& up,
                   const glm::vec3& right) noexcept
            : position(position),
              zNear(zNear), zFar(zFar), aspectRatio(aspectRatio), zoom(DEFAULT_ZOOM),
              forward(forward), up(up), right(right),
              projectionMatrix(), viewMatrix(), inverseProjectionMatrix(), inverseViewMatrix() {}

    void Camera::update(float dt) {
        adjustProjection();
        adjustView();
    }

    void Camera::adjustProjection() {}

    void Camera::adjustView() {}

    void Camera::handleMouseScroll(float yOffset) {}

    void Camera::handleMouseMovement(float xOffset, float yOffset, bool constrainPitch) {}

    void Camera::handleKeyboard(Direction direction, float dt) {}

    float Camera::getZNear() const noexcept {
        return zNear;
    }

    void Camera::setZNear(float newZNear) noexcept {
        zNear = newZNear;
    }

    float Camera::getZFar() const noexcept {
        return zFar;
    }

    void Camera::setZFar(float newZFar) noexcept {
        zFar = newZFar;
    }

    float Camera::getAspectRatio() const noexcept {
        return aspectRatio;
    }

    void Camera::setAspectRatio(float newAspectRatio) noexcept {
        aspectRatio = newAspectRatio;
    }

    float Camera::getZoom() const noexcept {
        return zoom;
    }

    void Camera::setZoom(float newZoom) noexcept {
        zoom = newZoom;
    }

    glm::vec3 Camera::getForward() const noexcept {
        return forward;
    }

    void Camera::setForward(const glm::vec3& newForward) noexcept {
        forward = newForward;
    }

    glm::vec3 Camera::getUp() const noexcept {
        return up;
    }

    void Camera::setUp(const glm::vec3& newUp) noexcept {
        up = newUp;
    }

    glm::vec3 Camera::getRight() const noexcept {
        return right;
    }

    void Camera::setRight(const glm::vec3& newRight) noexcept {
        right = newRight;
    }

    glm::mat4 Camera::getProjectionMatrix() const noexcept {
        return projectionMatrix;
    }

    glm::mat4 Camera::getInverseProjectionMatrix() const noexcept {
        return inverseProjectionMatrix;
    }

    glm::mat4 Camera::getViewMatrix() const noexcept {
        return viewMatrix;
    }

    glm::mat4 Camera::getInverseViewMatrix() const noexcept {
        return inverseViewMatrix;
    }
}

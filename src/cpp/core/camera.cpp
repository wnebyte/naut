#include <glm/ext/matrix_transform.hpp>
#include "core/camera.h"

namespace core {

    Camera::Camera(const glm::vec3& position, float zNear, float zFar, float aspectRatio) noexcept
            : position(position),
              zNear(zNear), zFar(zFar), aspectRatio(aspectRatio), zoom(1.0f),
              projectionMatrix(), viewMatrix(),
              inverseProjectionMatrix(), inverseViewMatrix() {}

    void Camera::update(float dt) {
        adjustProjection();
        adjustView();
    }

    void Camera::adjustProjection() {}

    void Camera::adjustView() {}

    void Camera::handleMouseScroll(float yOffset) {}

    void Camera::handleMouseMovement(float xOffset, float yOffset, bool constrainPitch) {}

    void Camera::handleKeyboard(Direction direction, float dt) {}

    glm::vec3 Camera::getPosition() const noexcept {
        return position;
    }

    void Camera::setPosition(float x, float y, float z) noexcept {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void Camera::setPosition(const glm::vec3& newPosition) noexcept {
        position = newPosition;
    }

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

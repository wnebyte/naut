#include <glm/ext/matrix_transform.hpp>
#include "core/camera.h"

namespace core {

    Camera::Camera(const glm::vec3& position)
            : position(position),
              projectionMatrix(), viewMatrix(),
              inverseProjectionMatrix(), inverseViewMatrix()
              {}

    void Camera::update(float dt)
    {
        adjustProjection();
        adjustView();
    }

    void Camera::adjustProjection()
    {}

    void Camera::adjustView()
    {}

    void Camera::handleMouseScroll(float yOffset)
    {}

    void Camera::handleMouseMovement(float xOffset, float yOffset, bool constrainPitch)
    {}

    void Camera::handleKeyboard(Movement direction, float dt)
    {}

    glm::vec3 Camera::getPosition() const noexcept
    {
        return position;
    }

    void Camera::setPosition(float x, float y, float z) noexcept
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void Camera::setPosition(const glm::vec3& newPosition) noexcept
    {
        position = newPosition;
    }

    glm::mat4 Camera::getProjectionMatrix() const noexcept
    {
        return projectionMatrix;
    }

    glm::mat4 Camera::getInverseProjectionMatrix() const noexcept
    {
        return inverseProjectionMatrix;
    }

    glm::mat4 Camera::getViewMatrix() const noexcept
    {
        return viewMatrix;
    }

    glm::mat4 Camera::getInverseViewMatrix() const noexcept
    {
        return inverseViewMatrix;
    }
}

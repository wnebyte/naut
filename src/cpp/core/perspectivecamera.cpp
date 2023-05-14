#include "glm.h"
#include "core/perspectivecamera.h"
#include "utility/math.h"

#define MIN_ZOOM     (1.0f)
#define MAX_ZOOM     (90.0f)
#define MIN_PITCH    (-90.0f)
#define MAX_PITCH    (90.0f)
#define YAW_WEIGHT   (1.7f)
#define PITCH_WEIGHT (0.1f)

namespace core {

    using namespace utility;

    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position,
                                         float zNear,
                                         float zFar,
                                         float aspectRatio,
                                         const glm::vec3& forward,
                                         const glm::vec3& up,
                                         const glm::vec3& right,
                                         float yaw,
                                         float pitch,
                                         float movementSpeed,
                                         float mouseSensitivity) noexcept
                                         : Camera(position, zNear, zFar, aspectRatio, forward, up, right),
                                           yaw(yaw), pitch(pitch), wUp(up),
                                           movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity)  {
                                             updateCameraVectors();
                                         }

    void PerspectiveCamera::update(float dt) {
        updateCameraVectors();
        Camera::update(dt);
    }

    void PerspectiveCamera::adjustProjection() {
        projectionMatrix = glm::perspective(glm::radians(zoom), aspectRatio, zNear, zFar);
        inverseProjectionMatrix = glm::inverse(projectionMatrix);
    }

    void PerspectiveCamera::adjustView() {
        viewMatrix = glm::lookAt(position, position + forward, up);
        inverseViewMatrix = glm::inverse(viewMatrix);
    }

    void PerspectiveCamera::updateCameraVectors() {
        // calculate and normalize the new forward vector
        forward.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        forward.y = glm::sin(pitch);
        forward.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        forward = glm::normalize(forward);
        // calculate and normalize the new right vector
        right = glm::normalize(glm::cross(forward, wUp));
        // calculate and normalize the new up vector
        up = glm::normalize(glm::cross(right, forward));
    }

    void PerspectiveCamera::handleMouseScroll(float yOffset) {
        zoom = math::clamp(zoom -= yOffset, MIN_ZOOM, MAX_ZOOM);
    }

    void PerspectiveCamera::handleMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
        xOffset *= mouseSensitivity;
        yOffset *= mouseSensitivity;
        yaw     += YAW_WEIGHT   * xOffset;
        pitch   += PITCH_WEIGHT * yOffset;

        if (constrainPitch) {
            pitch = math::clamp(pitch, MIN_PITCH, MAX_PITCH);
        }

        updateCameraVectors();
    }

    void PerspectiveCamera::handleKeyboard(Direction direction, float dt) {
        float velocity = movementSpeed * dt;

        switch (direction) {
            case Camera::Direction::Forward:
                position += forward * velocity;
                break;
            case Direction::Backward:
                position -= forward * velocity;
                break;
            case Direction::Left:
                position -= right * velocity;
                break;
            case Direction::Right:
                position += right * velocity;
                break;
            case Direction::Up:
                position += up * velocity;
                break;
            case Direction::Down:
                position -= up * velocity;
                break;
        }
    }

    float PerspectiveCamera::getYaw() const noexcept {
        return yaw;
    }

    void PerspectiveCamera::setYaw(float newYaw) noexcept {
        yaw = newYaw;
    }

    float PerspectiveCamera::getPitch() const noexcept {
        return pitch;
    }

    void PerspectiveCamera::setPitch(float newPitch) noexcept {
        pitch = newPitch;
    }

    float PerspectiveCamera::getMovementSpeed() const noexcept {
        return movementSpeed;
    }

    void PerspectiveCamera::setMovementSpeed(float newMovementSpeed) noexcept {
        movementSpeed = newMovementSpeed;
    }

    float PerspectiveCamera::getMouseSensitivity() const noexcept {
        return mouseSensitivity;
    }

    void PerspectiveCamera::setMouseSensitivity(float newMouseSensitivity) noexcept {
        mouseSensitivity = newMouseSensitivity;
    }
}

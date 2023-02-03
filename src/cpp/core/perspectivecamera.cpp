#include "core/perspectivecamera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace core {

    PerspectiveCamera::PerspectiveCamera(const glm::vec3& position,
                                         float zNear, float zFar, float aspect,
                                         const glm::vec3& forward, const glm::vec3& up, const glm::vec3& right,
                                         float yaw, float pitch, float zoom,
                                         float movementSpeed, float mouseSensitivity)
                                         : Camera(position),
                                           zNear(zNear), zFar(zFar), aspect(aspect),
                                           forward(forward), up(up), wUp(up), right(right),
                                           yaw(yaw), pitch(pitch), zoom(zoom),
                                           movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity)
                                         {
                                             updateCameraVectors();
                                         }

    void PerspectiveCamera::adjustProjection()
    {
        projectionMatrix = glm::perspective(glm::radians(zoom), aspect, zNear, zFar);
        inverseProjectionMatrix = glm::inverse(projectionMatrix);
    }

    void PerspectiveCamera::adjustView()
    {
        viewMatrix = glm::lookAt(position, position + forward, up);
        inverseViewMatrix = glm::inverse(viewMatrix);
    }

    void PerspectiveCamera::updateCameraVectors()
    {

    }

    float PerspectiveCamera::getZNear() const noexcept
    {
        return zNear;
    }

    void PerspectiveCamera::setZNear(float newZNear) noexcept
    {
        zNear = newZNear;
    }

    float PerspectiveCamera::getZFar() const noexcept
    {
        return zFar;
    }

    void PerspectiveCamera::setZFar(float newZFar) noexcept
    {
        zFar = newZFar;
    }

    float PerspectiveCamera::getAspect() const noexcept
    {
        return aspect;
    }

    void PerspectiveCamera::setAspect(float newAspect) noexcept
    {
        aspect = newAspect;
    }
}

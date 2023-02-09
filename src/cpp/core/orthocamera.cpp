#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "core/orthocamera.h"

namespace core {

    OrthoCamera::OrthoCamera(const glm::vec3& position,
                             int projectionWidth,
                             int projectionHeight,
                             const glm::vec3& viewEye,
                             const glm::vec3& viewCenter,
                             const glm::vec3& viewUp)
    : Camera(position),
      projectionWidth(projectionWidth), projectionHeight(projectionHeight),
      viewEye(viewEye), viewCenter(viewCenter), viewUp(viewUp)
    {}

    void OrthoCamera::adjustProjection()
    {
        float halfWidth  = static_cast<float>(projectionWidth)  / 2.0f;
        float halfHeight = static_cast<float>(projectionHeight) / 2.0f;
        projectionMatrix = glm::identity<glm::mat4>();
        projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
        inverseProjectionMatrix = glm::inverse(projectionMatrix);
    }

    void OrthoCamera::adjustView()
    {
        viewMatrix = glm::identity<glm::mat4>();
        viewMatrix = glm::lookAt(viewEye, viewCenter, viewUp);
        inverseViewMatrix = glm::inverse(viewMatrix);
    }

    int OrthoCamera::getProjectionWidth() const noexcept
    {
        return projectionWidth;
    }

    void OrthoCamera::setProjectionWidth(int newProjectionWidth) noexcept
    {
        projectionHeight = newProjectionWidth;
    }

    int OrthoCamera::getProjectionHeight() const noexcept
    {
        return projectionHeight;
    }

    void OrthoCamera::setProjectionHeight(int newProjectionWidth) noexcept
    {
        projectionWidth = newProjectionWidth;
    }

    glm::vec3 OrthoCamera::getViewEye() const noexcept
    {
        return viewEye;
    }

    void OrthoCamera::setViewEye(const glm::vec3& newEye) noexcept
    {
        viewEye = newEye;
    }

    glm::vec3 OrthoCamera::getViewCenter() const noexcept
    {
        return viewCenter;
    }

    void OrthoCamera::setViewCenter(const glm::vec3& newCenter) noexcept
    {
        viewCenter = newCenter;
    }

    glm::vec3 OrthoCamera::getViewUp() const noexcept
    {
        return viewUp;
    }

    void OrthoCamera::setViewUp(const glm::vec3& newUp) noexcept
    {
        viewUp = newUp;
    }
}

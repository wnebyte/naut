#ifndef NAUT_PERSPECTIVECAMERA_H
#define NAUT_PERSPECTIVECAMERA_H

#include "perspectivecamerafwd.h"
#include "camera.h"

#define DEFAULT_FORWARD glm::vec3{0.0f, 0.0f, -1.0f}
#define DEFAULT_UP glm::vec3{0.0f, 1.0f, 0.0f}
#define DEFAULT_RIGHT glm::vec3{1.0f, 0.0f, 0.0f}
#define DEFAULT_YAW -90.0f
#define DEFAULT_PITCH 0.0f
#define DEFAULT_ZOOM 0.0f
#define DEFAULT_MOVEMENT_SPEED 2.5f
#define DEFAULT_MOUSE_SENSITIVITY 0.08f

namespace core {
    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(const glm::vec3& position,
                          float zNear, float zFar, float aspect,
                          const glm::vec3& forward = DEFAULT_FORWARD,
                          const glm::vec3& up = DEFAULT_UP,
                          const glm::vec3& right = DEFAULT_RIGHT,
                          float yaw = DEFAULT_YAW,
                          float pitch = DEFAULT_PITCH,
                          float zoom = DEFAULT_ZOOM,
                          float movementSpeed = DEFAULT_MOVEMENT_SPEED,
                          float mouseSensitivity = DEFAULT_MOUSE_SENSITIVITY);

        ~PerspectiveCamera() noexcept = default;

        float getZNear() const noexcept;

        void setZNear(float newZNear) noexcept;

        float getZFar() const noexcept;

        void setZFar(float newZFar) noexcept;

        float getAspect() const noexcept;

        void setAspect(float newAspect) noexcept;

    protected:
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 wUp;
        glm::vec3 right;
        float zNear;
        float zFar;
        float aspect;
        float yaw;
        float pitch;
        float zoom;
        float movementSpeed;
        float mouseSensitivity;

        void adjustProjection() override;

        void adjustView() override;

        void updateCameraVectors();
    };
}

#endif //NAUT_PERSPECTIVECAMERA_H

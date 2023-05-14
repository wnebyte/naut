#ifndef NAUT_CAMERA_H
#define NAUT_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "camerafwd.h"

#define CAMERA_DEFAULT_FORWARD (glm::vec3{0.0f, 0.0f, -1.0f})
#define CAMERA_DEFAULT_UP      (glm::vec3{0.0f, 1.0f, 0.0f})
#define CAMERA_DEFAULT_RIGHT   (glm::vec3{1.0f, 0.0f, 0.0f})

namespace core {
    class Camera {
    public:
        enum class Direction {
            Forward,
            Backward,
            Left,
            Right,
            Up,
            Down
        };

        glm::vec3 position;

        Camera(const glm::vec3& position,
               float zNear,
               float zFar,
               float aspectRatio,
               const glm::vec3& forward = CAMERA_DEFAULT_FORWARD,
               const glm::vec3& up      = CAMERA_DEFAULT_UP,
               const glm::vec3& right   = CAMERA_DEFAULT_RIGHT) noexcept;

        virtual ~Camera() noexcept = default;

        virtual void update(float dt);

        virtual void handleMouseScroll(float yOffset);

        virtual void handleMouseMovement(float xOffset, float yOffset, bool constrainPitch);

        virtual void handleKeyboard(Direction direction, float dt);

        float getZNear() const noexcept;

        void setZNear(float) noexcept;

        float getZFar() const noexcept;

        void setZFar(float) noexcept;

        float getAspectRatio() const noexcept;

        void setAspectRatio(float) noexcept;

        float getZoom() const noexcept;

        void setZoom(float) noexcept;

        glm::vec3 getForward() const noexcept;

        void setForward(const glm::vec3&) noexcept;

        glm::vec3 getUp() const noexcept;

        void setUp(const glm::vec3&) noexcept;

        glm::vec3 getRight() const noexcept;

        void setRight(const glm::vec3&) noexcept;

        glm::mat4 getProjectionMatrix() const noexcept;

        glm::mat4 getInverseProjectionMatrix() const noexcept;

        glm::mat4 getViewMatrix() const noexcept;

        glm::mat4 getInverseViewMatrix() const noexcept;

    protected:
        float zNear;
        float zFar;
        float aspectRatio;
        float zoom;
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 right;
        glm::mat4 projectionMatrix;
        glm::mat4 inverseProjectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 inverseViewMatrix;

        virtual void adjustProjection();

        virtual void adjustView();
    };

}

#endif //NAUT_CAMERA_H

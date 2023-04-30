#ifndef NAUT_CAMERA_H
#define NAUT_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "camerafwd.h"

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

        Camera(const glm::vec3& position, float zNear, float zFar, float aspectRatio) noexcept;

        virtual ~Camera() noexcept = default;

        virtual void update(float dt);

        virtual void handleMouseScroll(float yOffset);

        virtual void handleMouseMovement(float xOffset, float yOffset, bool constrainPitch);

        virtual void handleKeyboard(Direction direction, float dt);

        glm::vec3 getPosition() const noexcept;

        void setPosition(float x, float y, float z) noexcept;

        void setPosition(const glm::vec3&) noexcept;

        float getZNear() const noexcept;

        void setZNear(float) noexcept;

        float getZFar() const noexcept;

        void setZFar(float) noexcept;

        float getAspectRatio() const noexcept;

        void setAspectRatio(float) noexcept;

        float getZoom() const noexcept;

        void setZoom(float) noexcept;

        glm::mat4 getProjectionMatrix() const noexcept;

        glm::mat4 getInverseProjectionMatrix() const noexcept;

        glm::mat4 getViewMatrix() const noexcept;

        glm::mat4 getInverseViewMatrix() const noexcept;

    protected:
        glm::vec3 position;
        float zNear;
        float zFar;
        float aspectRatio;
        float zoom;
        glm::mat4 projectionMatrix;
        glm::mat4 inverseProjectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 inverseViewMatrix;

        virtual void adjustProjection();

        virtual void adjustView();
    };

}

#endif //NAUT_CAMERA_H

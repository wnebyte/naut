#ifndef NAUT_ORTHOCAMERA_H
#define NAUT_ORTHOCAMERA_H

#include "orthocamerafwd.h"
#include "camera.h"

#define DEFAULT_VIEW_EYE glm::vec3{0.0f, 0.0f, 10.0f}
#define DEFAULT_VIEW_CENTER glm::vec3{0.0f, 0.0f, 9.0f}
#define DEFAULT_VIEW_UP glm::vec3{0.0f, 1.0f, 0.0f}

namespace core {
    class OrthoCamera : public Camera {
    public:
        OrthoCamera(const glm::vec3& position,
                    int projectionWidth,
                    int projectionHeight,
                    const glm::vec3& viewEye = DEFAULT_VIEW_EYE,
                    const glm::vec3& viewCenter = DEFAULT_VIEW_CENTER,
                    const glm::vec3& viewUp = DEFAULT_VIEW_UP);

        ~OrthoCamera() noexcept = default;

        int getProjectionWidth() const noexcept;

        void setProjectionWidth(int newProjectionWidth) noexcept;

        int getProjectionHeight() const noexcept;

        void setProjectionHeight(int newProjectionHeight) noexcept;

        glm::vec3 getViewEye() const noexcept;

        void setViewEye(const glm::vec3& newEye) noexcept;

        glm::vec3 getViewCenter() const noexcept;

        void setViewCenter(const glm::vec3& newCenter) noexcept;

        glm::vec3 getViewUp() const noexcept;

        void setViewUp(const glm::vec3& newUp) noexcept;

    protected:
        int projectionWidth;
        int projectionHeight;
        glm::vec3 viewEye;
        glm::vec3 viewCenter;
        glm::vec3 viewUp;

        void adjustProjection() override;

        void adjustView() override;
    };
}

#endif //NAUT_ORTHOCAMERA_H

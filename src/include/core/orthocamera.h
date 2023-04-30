#ifndef NAUT_ORTHOCAMERA_H
#define NAUT_ORTHOCAMERA_H

#include "orthocamerafwd.h"
#include "camera.h"

#define DEFAULT_VIEW_EYE    (glm::vec3{0.0f, 0.0f, 10.0f})
#define DEFAULT_VIEW_CENTER (glm::vec3{0.0f, 0.0f, 9.0f})
#define DEFAULT_VIEW_UP     (glm::vec3{0.0f, 1.0f, 0.0f})

namespace core {
    class OrthoCamera : public Camera {
    public:
        OrthoCamera(const glm::vec3& position,
                    int32_t projectionWidth,
                    int32_t projectionHeight,
                    float zNear,
                    float zFar,
                    float aspectRatio,
                    const glm::vec3& viewEye = DEFAULT_VIEW_EYE,
                    const glm::vec3& viewCenter = DEFAULT_VIEW_CENTER,
                    const glm::vec3& viewUp = DEFAULT_VIEW_UP) noexcept;

        ~OrthoCamera() noexcept = default;

        int32_t getProjectionWidth() const noexcept;

        void setProjectionWidth(int32_t newProjectionWidth) noexcept;

        int32_t getProjectionHeight() const noexcept;

        void setProjectionHeight(int32_t newProjectionHeight) noexcept;

        glm::vec3 getViewEye() const noexcept;

        void setViewEye(const glm::vec3& newViewEye) noexcept;

        glm::vec3 getViewCenter() const noexcept;

        void setViewCenter(const glm::vec3& newViewCenter) noexcept;

        glm::vec3 getViewUp() const noexcept;

        void setViewUp(const glm::vec3& newViewUp) noexcept;

    private:
        int32_t projectionWidth;
        int32_t projectionHeight;
        glm::vec3 viewEye;
        glm::vec3 viewCenter;
        glm::vec3 viewUp;

        void adjustProjection() override;

        void adjustView() override;
    };
}

#endif //NAUT_ORTHOCAMERA_H

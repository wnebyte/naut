#ifndef NAUT_ORTHOCAMERA_H
#define NAUT_ORTHOCAMERA_H

#include "orthocamerafwd.h"
#include "camera.h"

namespace core {
    class OrthoCamera : public Camera {
    public:
        OrthoCamera(const glm::vec3& position,
                    int32_t projectionWidth,
                    int32_t projectionHeight,
                    float zNear,
                    float zFar,
                    float aspectRatio,
                    const glm::vec3& forward = CAMERA_DEFAULT_FORWARD,
                    const glm::vec3& up      = CAMERA_DEFAULT_UP,
                    const glm::vec3& right   = CAMERA_DEFAULT_RIGHT) noexcept;

        ~OrthoCamera() noexcept = default;

        int32_t getProjectionWidth() const noexcept;

        void setProjectionWidth(int32_t) noexcept;

        int32_t getProjectionHeight() const noexcept;

        void setProjectionHeight(int32_t) noexcept;

    private:
        int32_t projectionWidth;
        int32_t projectionHeight;

        void adjustProjection() override;

        void adjustView() override;
    };
}

#endif //NAUT_ORTHOCAMERA_H

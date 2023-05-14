#include <array>
#include <algorithm>
#include "io/mouselistener.h"
#include "core/camera.h"

#define N_BUTTONS (9u)

namespace io {

    namespace mouselistener {

        static float xPos = 0.0f;

        static float yPos = 0.0f;

        static double xScroll = 0.0;

        static double yScroll = 0.0;

        static std::array<bool, N_BUTTONS> mouseButtonDown{};

        static std::array<bool, N_BUTTONS> mouseButtonPressed{};

        static bool dragging = false;

        static int nMouseButtonDown = 0;

        static bool firstMouse = true;

        static std::function<std::shared_ptr<Camera>()> fnGetCamera{};

        void init(std::function<std::shared_ptr<Camera>()> newFnGetCamera) {
            fnGetCamera = newFnGetCamera;
        }

        void endFrame() {
            std::fill(mouseButtonPressed.begin(), mouseButtonPressed.end(), false);
        }

        void cursorPosCallback(GLFWwindow*, double x, double y) {
            if (firstMouse) {
                xPos = x;
                yPos = y;
                firstMouse = false;
            }

            dragging = (nMouseButtonDown > 0);
            float xOffset = x - xPos;
            float yOffset = yPos - y; // reversed since y-coordinates go from bottom to top
            xPos = x;
            yPos = y;

            std::shared_ptr<Camera> camera = fnGetCamera();
            if (camera && (xOffset > 0.0f || yOffset > 0.0f)) {
                camera->handleMouseMovement(xOffset, yOffset, true);
            }
        }

        void mouseButtonCallback(GLFWwindow*, int button, int action, int) {
            if (action == GLFW_PRESS) {
                ++nMouseButtonDown;
                if (button < N_BUTTONS) {
                    mouseButtonDown[button] = true;
                    mouseButtonPressed[button] = true;
                }
            } else if (action == GLFW_RELEASE) {
                --nMouseButtonDown;
                if (button < N_BUTTONS) {
                    mouseButtonDown[button] = false;
                    mouseButtonPressed[button] = false;
                    dragging = false;
                }
            }
        }

        void scrollCallback(GLFWwindow*, double xOffset, double yOffset) {
            xScroll = xOffset;
            yScroll = yOffset;

            std::shared_ptr<Camera> camera = fnGetCamera();
            if (camera && yOffset > 0.0f) {
                camera->handleMouseScroll(yOffset);
            }
        }

        bool isMouseButtonDown(int button) {
            if (button < N_BUTTONS) {
                return mouseButtonDown[button];
            } else {
                return false;
            }
        }

        bool isMouseButtonPressed(int button) {
            if (button < N_BUTTONS) {
                return mouseButtonPressed[button];
            } else {
                return false;
            }
        }

        bool isDragging() {
            return dragging;
        }

        float getX() {
            return xPos;
        }

        float getY() {
            return yPos;
        }

        float getScrollX() {
            return xScroll;
        }

        float getScrollY() {
            return yScroll;
        }

//        glm::vec2& getWorldCoords(glm::vec2& dest) {
//            std::shared_ptr<Camera> camera = fnGetCamera();
//            float x = xPos - viewportPos.x;
//            x = (x / viewportSize.x) * 2.0f - 1.0f;
//            float y = yPos - viewportPos.y;
//            yPos = -((y / viewportSize.y) * 2.0f - 1.0f);
//            glm::vec4 tmp{x, y, 0.0f, 1.0f};
//            tmp = (tmp * (camera->getInverseViewMatrix() * camera->getInverseProjectionMatrix()));
//            dest.x = tmp.x;
//            dest.y = tmp.y;
//            return dest;
//        }
//
//        glm::vec2& getScreenCoords(glm::vec2& dest) {
//            constexpr int32_t w = 1920, h = 1080;
//            std::shared_ptr<Camera> camera = fnGetCamera();
//            float x = xPos - viewportPos.x;
//            x = (x / viewportSize.x) * w;
//            float y = yPos - viewportPos.y;
//            y = h - ((y / viewportSize.y) * h);
//            dest.x = x;
//            dest.y = y;
//            return dest;
//        }
//
//        glm::vec2& screenCoordsToWorldCoords(const glm::ivec2& screenCoords, glm::vec2& dest) {
//            constexpr int32_t w = 1920, h = 1080;
//            std::shared_ptr<Camera> camera = fnGetCamera();
//            glm::vec2 norm{screenCoords.x / w, screenCoords.y / h};
//            norm = (norm * 2.0f) - 1.0f;
//            glm::vec4 tmp{norm.x, norm.y, 0.0f, 1.0f};
//            tmp = (tmp * (camera->getInverseViewMatrix() * camera->getInverseProjectionMatrix()));
//            dest.x = tmp.x;
//            dest.y = tmp.y;
//            return dest;
//        }
//
//        glm::vec2& worldCoordsToScreenCoords(const glm::vec2& worldCoords, glm::vec2& dest) {
//            constexpr int32_t w = 1920, h = 1080;
//            std::shared_ptr<Camera> camera = fnGetCamera();
//            glm::vec4 ndcSpacePos{worldCoords.x, worldCoords.y, 0.0f, 1.0f};
//            ndcSpacePos = (ndcSpacePos * (camera->getProjectionMatrix() * camera->getViewMatrix()));
//            glm::vec2 windowSpace = glm::vec2{ndcSpacePos.x, ndcSpacePos.y} * (1.0f - ndcSpacePos.w);
//            windowSpace += (glm::vec2{1.0f, 1.0f} * 0.5f);
//            windowSpace = (windowSpace * glm::vec2{w, h});
//            dest.x = windowSpace.x;
//            dest.y = windowSpace.y;
//            return dest;
//        }
    }
}

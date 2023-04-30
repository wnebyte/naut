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
        static std::array<bool, N_BUTTONS> mouseButtonPressed{};
        static std::array<bool, N_BUTTONS> mouseButtonJustPressed{};
        static bool dragging = false;
        static int mouseButtonDown = 0;
        static bool firstMouse = true;
        static std::function<std::shared_ptr<Camera>()> fnGetCamera{};

        void init(std::function<std::shared_ptr<Camera>()> fn) {
            fnGetCamera = fn;
        }

        void endFrame() {
            std::fill(mouseButtonJustPressed.begin(), mouseButtonJustPressed.end(), false);
        }

        void cursorPosCallback(GLFWwindow*, double x, double y) {
            dragging = (mouseButtonDown > 0);
            if (firstMouse) {
                xPos = x;
                yPos = y;
                firstMouse = false;
            }

            float xOffset = x - xPos;
            float yOffset = yPos - y; // reversed since y-coordinates go from bottom to top
            xPos = x;
            yPos = y;

            std::shared_ptr<Camera> camera = fnGetCamera();
            if (camera) {
                camera->handleMouseMovement(xOffset, yOffset, true);
            }
        }

        void mouseButtonCallback(GLFWwindow*, int button, int action, int mod) {
            if (action == GLFW_PRESS) {
                ++mouseButtonDown;
                if (button < N_BUTTONS) {
                    mouseButtonPressed[button] = true;
                    mouseButtonJustPressed[button] = true;
                }
            } else if (action == GLFW_RELEASE) {
                --mouseButtonDown;
                if (button < N_BUTTONS) {
                    mouseButtonPressed[button] = false;
                    mouseButtonJustPressed[button] = false;
                    dragging = false;
                }
            }
        }

        void scrollCallback(GLFWwindow*, double xOffset, double yOffset) {
            xScroll = xOffset;
            yScroll = yOffset;

            std::shared_ptr<Camera> camera = fnGetCamera();
            if (camera) {
                camera->handleMouseScroll(yOffset);
            }
        }

        bool isMouseButtonDown(int button) {
            if (button < N_BUTTONS) {
                return mouseButtonPressed[button];
            } else {
                return false;
            }
        }

        bool isMouseButtonBeginDown(int button) {
            if (button < N_BUTTONS) {
                return mouseButtonJustPressed[button];
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
    }
}
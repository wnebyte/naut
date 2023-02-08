#include <algorithm>
#include "core/mouselistener.h"
#include "core/camera.h"

namespace core {

    static float xPos = 0.0f;

    static float yPos = 0.0f;

    static double xScroll = 0.0;

    static double yScroll = 0.0;

    static std::array<bool, 9> mouseButtonPressed{};

    static std::array<bool, 9> mouseButtonBeginPressed{};

    static bool dragging = false;

    static int mouseButtonDown = 0;

    static bool firstMouse = true;

    static std::function<Camera* const()> callback{};

    void MouseListener::init(std::function<Camera *const()> c) {
        callback = c;
    }

    void MouseListener::endFrame() {
        std::fill(mouseButtonBeginPressed.begin(), mouseButtonBeginPressed.end(), false);
    }

    void MouseListener::cursorPosCallback(GLFWwindow*, double x, double y) {
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

        Camera* const camera = callback();
        if (camera != nullptr) {
            camera->handleMouseMovement(xOffset, yOffset, true);
        }
    }

    void MouseListener::mouseButtonCallback(GLFWwindow*, int button, int action, int mod) {
        if (action == GLFW_PRESS) {
            ++mouseButtonDown;
            if (button < mouseButtonPressed.size()) {
                mouseButtonPressed[button] = true;
                mouseButtonBeginPressed[button] = true;
            }
        } else if (action == GLFW_RELEASE) {
            --mouseButtonDown;
            if (button < mouseButtonPressed.size()) {
                mouseButtonPressed[button] = false;
                mouseButtonBeginPressed[button] = false;
                dragging = false;
            }
        }
    }

    void MouseListener::scrollCallback(GLFWwindow*, double xOffset, double yOffset) {
        xScroll = xOffset;
        yScroll = yOffset;

        Camera* const camera = callback();
        if (camera != nullptr) {
            camera->handleMouseScroll(yOffset);
        }
    }

    bool MouseListener::isMouseButtonDown(int button) {
        if (button < mouseButtonPressed.size()) {
            return mouseButtonPressed[button];
        } else {
            return false;
        }
    }

    bool MouseListener::isMouseButtonBeginDown(int button) {
        if (button < mouseButtonBeginPressed.size()) {
            return mouseButtonBeginPressed[button];
        } else {
            return false;
        }
    }

    bool MouseListener::isDragging() {
        return dragging;
    }

    float MouseListener::getX() {
        return xPos;
    }

    float MouseListener::getY() {
        return yPos;
    }

    float MouseListener::getScrollX() {
        return xScroll;
    }

    float MouseListener::getScrollY() {
        return yScroll;
    }
}
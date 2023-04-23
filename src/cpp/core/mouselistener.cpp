#include <algorithm>
#include "core/mouselistener.h"
#include "core/camera.h"

#define N_BUTTONS (9u)

namespace core {

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

    void MouseListener::init(std::function<std::shared_ptr<Camera>()> fn) {
        fnGetCamera = fn;
    }

    void MouseListener::endFrame() {
        std::fill(mouseButtonJustPressed.begin(), mouseButtonJustPressed.end(), false);
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

        std::shared_ptr<Camera> camera = fnGetCamera();
        if (camera) {
            camera->handleMouseMovement(xOffset, yOffset, true);
        }
    }

    void MouseListener::mouseButtonCallback(GLFWwindow*, int button, int action, int mod) {
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

    void MouseListener::scrollCallback(GLFWwindow*, double xOffset, double yOffset) {
        xScroll = xOffset;
        yScroll = yOffset;

        std::shared_ptr<Camera> camera = fnGetCamera();
        if (camera) {
            camera->handleMouseScroll(yOffset);
        }
    }

    bool MouseListener::isMouseButtonDown(int button) {
        if (button < N_BUTTONS) {
            return mouseButtonPressed[button];
        } else {
            return false;
        }
    }

    bool MouseListener::isMouseButtonBeginDown(int button) {
        if (button < N_BUTTONS) {
            return mouseButtonJustPressed[button];
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
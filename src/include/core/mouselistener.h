#ifndef NAUT_MOUSELISTENER_H
#define NAUT_MOUSELISTENER_H

#include <array>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "mouselistenerfwd.h"
#include "camerafwd.h"

namespace core {
    class MouseListener {
    public:
        static void init(std::function<Camera* const()>);

        static void endFrame();

        static void cursorPosCallback(GLFWwindow*, double x, double y);

        static void mouseButtonCallback(GLFWwindow*, int button, int action, int mod);

        static void scrollCallback(GLFWwindow*, double xOffset, double yOffset);

        static bool isMouseButtonDown(int button);

        static bool isMouseButtonBeginDown(int button);

        static bool isDragging();

        static float getX();

        static float getY();

        static float getScrollX();

        static float getScrollY();
    };
}

#endif //NAUT_MOUSELISTENER_H

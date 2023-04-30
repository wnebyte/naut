#ifndef NAUT_MOUSELISTENER_H
#define NAUT_MOUSELISTENER_H

#include <memory>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/camerafwd.h"

using namespace core;

namespace io {
    namespace mouselistener {
        void init(std::function<std::shared_ptr<Camera>()>);

        void endFrame();

        void cursorPosCallback(GLFWwindow*, double x, double y);

        void mouseButtonCallback(GLFWwindow*, int button, int action, int mod);

        void scrollCallback(GLFWwindow*, double xOffset, double yOffset);

        bool isMouseButtonDown(int button);

        bool isMouseButtonBeginDown(int button);

        bool isDragging();

        float getX();

        float getY();

        float getScrollX();

        float getScrollY();
    }
}

#endif //NAUT_MOUSELISTENER_H

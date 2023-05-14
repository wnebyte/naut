#ifndef NAUT_MOUSELISTENER_H
#define NAUT_MOUSELISTENER_H

#include <memory>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/camerafwd.h"

namespace io {
    namespace mouselistener {
        using namespace core;

        void init(std::function<std::shared_ptr<Camera>()>);

        void endFrame();

        void cursorPosCallback(GLFWwindow*, double x, double y);

        void mouseButtonCallback(GLFWwindow*, int button, int action, int mod);

        void scrollCallback(GLFWwindow*, double xOffset, double yOffset);

        /**
         * Returns whether the mouse button associated with the specified <code>button</code> is currently down.
         * @param button the button
         * @return <code>true</code> if the specified button is down,
         * otherwise <code>false</code>
         */
        bool isMouseButtonDown(int button);

        /**
         * Returns whether the mouse button associated with the specified <code>button</code> was pressed during this frame.
         * @param button the button
         * @return <code>true</code> if the specified button was pressed during this frame,
         * otherwise <code>false</code>
         */
        bool isMouseButtonPressed(int button);

        bool isDragging();

        float getX();

        float getY();

        float getScrollX();

        float getScrollY();
    }
}

#endif //NAUT_MOUSELISTENER_H

#ifndef NAUT_KEYLISTENER_H
#define NAUT_KEYLISTENER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace io {
    namespace keylistener {
        void endFrame();

        void keyCallback(GLFWwindow*, int keyCode, int scanCode, int action, int mods);

        /**
         * Returns whether the key associated with the specified <code>keyCode</code> is currently down.
         * @param keyCode the keyCode
         * @return <code>true</code> if the specified key is down,
         * otherwise <code>false</code>
         */
        bool isKeyDown(int keyCode);

        /**
         * Returns whether the key associated with the specified <code>keyCode</code> was pressed during this frame.
         * @param keyCode the keyCode
         * @return <code>true</code> if the specified key was pressed during this frame,
         * otherwise <code>false</code>
         */
        bool isKeyPressed(int keyCode);
    }
}

#endif //NAUT_KEYLISTENER_H

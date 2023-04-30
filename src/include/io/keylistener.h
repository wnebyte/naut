#ifndef NAUT_KEYLISTENER_H
#define NAUT_KEYLISTENER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace io {
    namespace keylistener {
        void endFrame();

        void keyCallback(GLFWwindow*, int keyCode, int scanCode, int action, int mods);

        bool isKeyPressed(int keyCode);

        bool isKeyJustPressed(int keyCode);
    }
}

#endif //NAUT_KEYLISTENER_H

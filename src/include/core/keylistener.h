#ifndef NAUT_KEYLISTENER_H
#define NAUT_KEYLISTENER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "keylistenerfwd.h"

namespace core {
    class KeyListener {
    public:
        static void endFrame();

        static void keyCallback(GLFWwindow*, int key, int scanCode, int action, int mods);

        static bool isKeyPressed(int keyCode);

        static bool isKeyBeginPressed(int keyCode);
    };
}

#endif //NAUT_KEYLISTENER_H

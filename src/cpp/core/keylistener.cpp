#include <array>
#include "core/keylistener.h"

#define N_KEYS (350u)

namespace core {

    static std::array<bool, N_KEYS> keyPressed{};

    static std::array<bool, N_KEYS> keyJustPressed{};

    void KeyListener::endFrame() {
        std::fill(keyJustPressed.begin(), keyJustPressed.end(), false);
    }

    void KeyListener::keyCallback(GLFWwindow*, int keyCode, int, int action, int) {
        if (action == GLFW_PRESS) {
            if (keyCode < N_KEYS) {
                keyPressed[keyCode] = true;
                keyJustPressed[keyCode] = true;
            }
        } else if (action == GLFW_RELEASE) {
            if (keyCode < N_KEYS) {
                keyPressed[keyCode] = false;
                keyJustPressed[keyCode] = false;
            }
        }
    }

    bool KeyListener::isKeyPressed(int keyCode) {
        return keyPressed[keyCode];
    }

    bool KeyListener::isKeyJustPressed(int keyCode) {
        return keyJustPressed[keyCode];
    }
}

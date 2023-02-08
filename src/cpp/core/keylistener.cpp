#include <array>
#include "core/keylistener.h"

namespace core {

    static std::array<bool, 350> keyPressed{};

    static std::array<bool, 350> keyBeginPressed{};

    void KeyListener::endFrame() {
        std::fill(keyBeginPressed.begin(), keyBeginPressed.end(), false);
    }

    void KeyListener::keyCallback(GLFWwindow*, int key, int scanCode, int action, int mods) {
        if (action == GLFW_PRESS) {
            if (key < keyPressed.size()) {
                keyPressed[key] = true;
                keyBeginPressed[key] = true;
            }
        } else if (action == GLFW_RELEASE) {
            if (key < keyPressed.size()) {
                keyPressed[key] = false;
                keyBeginPressed[key] = false;
            }
        }
    }

    bool KeyListener::isKeyPressed(int keyCode) {
        return keyPressed[keyCode];
    }

    bool KeyListener::isKeyBeginPressed(int keyCode) {
        return keyBeginPressed[keyCode];
    }
}

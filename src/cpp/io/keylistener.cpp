#include <array>
#include "io/keylistener.h"

#define N_KEYS (350u)

namespace io {

    namespace keylistener {

        static std::array<bool, N_KEYS> keyDown{};

        static std::array<bool, N_KEYS> keyPressed{};

        void endFrame() {
            std::fill(keyPressed.begin(), keyPressed.end(), false);
        }

        void keyCallback(GLFWwindow*, int keyCode, int, int action, int) {
            if (action == GLFW_PRESS) {
                if (keyCode < N_KEYS) {
                    keyDown[keyCode] = true;
                    keyPressed[keyCode] = true;
                }
            } else if (action == GLFW_RELEASE) {
                if (keyCode < N_KEYS) {
                    keyDown[keyCode] = false;
                    keyPressed[keyCode] = false;
                }
            }
        }

        bool isKeyDown(int keyCode) {
            if (keyCode < N_KEYS) {
                return keyDown[keyCode];
            } else {
                return false;
            }
        }

        bool isKeyPressed(int keyCode) {
            if (keyCode < N_KEYS) {
                return keyPressed[keyCode];
            } else {
                return false;
            }
        }
    }
}

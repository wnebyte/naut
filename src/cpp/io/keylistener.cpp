#include <array>
#include "io/keylistener.h"

#define N_KEYS (350u)

namespace io {

    namespace keylistener {

        static std::array<bool, N_KEYS> keyPressed{};
        static std::array<bool, N_KEYS> keyJustPressed{};

        void endFrame() {
            std::fill(keyJustPressed.begin(), keyJustPressed.end(), false);
        }

        void keyCallback(GLFWwindow*, int keyCode, int, int action, int) {
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

        bool isKeyPressed(int keyCode) {
            if (keyCode < N_KEYS) {
                return keyPressed[keyCode];
            } else {
                return false;
            }
        }

        bool isKeyJustPressed(int keyCode) {
            if (keyCode < N_KEYS) {
                return keyJustPressed[keyCode];
            } else {
                return false;
            }
        }
    }
}

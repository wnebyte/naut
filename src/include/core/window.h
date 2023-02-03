#ifndef NAUT_WINDOW_H
#define NAUT_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <memory>
#include "windowfwd.h"

namespace core {
    class Window {
    private:
        GLFWwindow* glfwWindow;
        std::string title;
        int width;
        int height;

        explicit Window(const std::string&, int = 0, int = 0);
        void init();

    public:
        static Window* newInstance(const std::string&, int = 0, int = 0);

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        void update(float dt);
        void destroy();

        void setWindowTitle(const std::string&);
        void setWindowSize(int, int);

        std::string getTitle() const noexcept;
        int getWidth() const noexcept;
        int getHeight() const noexcept;
    };

}

#endif //NAUT_WINDOW_H

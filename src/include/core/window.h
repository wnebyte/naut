#ifndef NAUT_WINDOW_H
#define NAUT_WINDOW_H

#include <string>
#include <memory>
#include <utility>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "windowfwd.h"

namespace core {
    class Window {
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

    private:
        GLFWwindow* glfwWindow;
        std::string title;
        int width;
        int height;

        explicit Window(const std::string&, int, int);

        void init();

    };

}

#endif //NAUT_WINDOW_H

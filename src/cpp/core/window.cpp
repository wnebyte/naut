#include <iostream>
#include <glm/vec2.hpp>
#include "core/window.h"
#include "core/scene.h"
#include "core/camera.h"
#include "io/keylistener.h"
#include "io/mouselistener.h"

#define DEFAULT_WIDTH  (1920)
#define DEFAULT_HEIGHT (1080)

namespace core {

    using namespace io;

    static Window* window = nullptr;

    Window* Window::newInstance(const std::string& title, int width, int height) {
        if (window == nullptr) {
            window = new Window{title, width, height};
            return window;
        } else {
            throw std::exception{};
        }
    }

    Window* Window::getInstance() {
        if (window != nullptr) {
            return window;
        } else {
            throw std::exception{};
        }
    }

    static glm::ivec2 getMaxResolution(GLFWmonitor* monitor) {
        int width = 0, height = 0, size = 0;
        bool found = false;

        int count;
        const GLFWvidmode* const vidmode = glfwGetVideoModes(monitor, &count);
        if (vidmode != NULL) {
            for (int i = 0; i < count; ++i) {
                int w = vidmode[i].width;
                int h = vidmode[i].height;
                int sz = w * h;
                if (sz > size) {
                    width = w;
                    height = h;
                    size = sz;
                    found = true;
                }
            }
        }

        return found ? glm::ivec2{width, height} : glm::ivec2{DEFAULT_WIDTH, DEFAULT_HEIGHT};
    }

    static void framebufferSizeCallback(GLFWwindow*, int w, int h) {
        if (window) {
            window->setSize(w, h);
        }
    }

    Window::Window(const std::string& title, int width, int height)
            : glfwWindow(nullptr), scene(nullptr), title(title), width(width), height(height) {
        init();
        scene = std::shared_ptr<Scene>{new Scene{this}};
    }

    Window::~Window() noexcept {
        try {
            glfwSetErrorCallback(NULL);
            glfwDestroyWindow(glfwWindow);
            glfwTerminate();
        } catch ( ... ) {}
    }

    void Window::init() {
        // Setup an error callback
        glfwSetErrorCallback([](int, const char* msg) { std::cerr << msg << '\n'; });

        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "Unable to initialize GLFW." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (width <= 0 || height <= 0) {
            glm::ivec2 res = getMaxResolution(glfwGetPrimaryMonitor());
            width  = res.x;
            height = res.y;
        }

        mouselistener::init([this](){ return scene ? scene->getCamera() : nullptr; });

        // Configure GLFW
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

        // Create the window
        glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (glfwWindow == NULL) {
            std::cerr << "Failed to create GLFW window." << std::endl;
            std::exit(EXIT_FAILURE);
        }
        // Make OpenGL context current
        glfwMakeContextCurrent(glfwWindow);

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Set callbacks
        glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);
        glfwSetCursorPosCallback(glfwWindow, mouselistener::cursorPosCallback);
        glfwSetMouseButtonCallback(glfwWindow, mouselistener::mouseButtonCallback);
        glfwSetScrollCallback(glfwWindow, mouselistener::scrollCallback);
        glfwSetKeyCallback(glfwWindow, keylistener::keyCallback);
        glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Enable v-sync
        glfwSwapInterval(1);

        // Make the window visible
        glfwShowWindow(glfwWindow);

        glViewport(0, 0, width, height);
    }

    void Window::update(float dt) {
        if (scene) {
            scene->update(dt);
        }
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(glfwWindow);
    }

    void Window::pollEvents(float dt) {
        glfwPollEvents();
        if (scene) {
            scene->processInput(dt);
        }
    }

    void Window::setInputMode(int mode, int value) {
        glfwSetInputMode(glfwWindow, mode, value);
    }

    void Window::setCursorMode(int value) {
        setInputMode(GLFW_CURSOR, value);
    }

    void Window::setCursorPos(double xPos, double yPos) {
        glfwSetCursorPos(glfwWindow, xPos, yPos);
    }

    void Window::setShouldClose(bool value) {
        glfwSetWindowShouldClose(glfwWindow, value);
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(glfwWindow);
    }

    void Window::setSize(int newWidth, int newHeight) {
        width  = newWidth;
        height = newHeight;
        glViewport(0, 0, width, height);
    }

    void Window::setTitle(const std::string& newTitle) {
        title = newTitle;
        glfwSetWindowTitle(glfwWindow, title.c_str());
    }

    std::string Window::getTitle() const noexcept {
        return title;
    }

    int Window::getWidth() const noexcept {
        return width;
    }

    int Window::getHeight() const noexcept {
        return height;
    }

    float Window::getAspectRatio() const {
        float w = static_cast<float>(width);
        float h = static_cast<float>(height);
        return w / h;
    }

    void Window::setScene(const std::shared_ptr<Scene>& newScene) {
        scene = newScene;
    }

    std::shared_ptr<Scene> Window::getScene() const noexcept {
        return scene;
    }
}

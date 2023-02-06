#include <glm/vec2.hpp>
#include <iostream>
#include "core/window.h"
#include "core/camera.h"
#include "core/perspectivecamera.h"
#include "renderer/shader.h"
#include "renderer/boxrenderer.h"

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080

namespace core {

    using namespace renderer;

    static Window* window = nullptr;

    Window* Window::newInstance(const std::string& title, int width, int height)
    {
        if (window == nullptr) {
            window = new Window{title, width, height};
            return window;
        } else {
            return nullptr;
        }
    }

    static glm::ivec2 getMaxResolution(GLFWmonitor* monitor)
    {
        int width = 0;
        int height = 0;
        int size = 0;
        bool found = false;

        int count;
        const GLFWvidmode* vidmode = glfwGetVideoModes(monitor, &count);
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

    Window::Window(const std::string& title, int width, int height)
            : glfwWindow(nullptr), title(title), width(width), height(height)
    {
        init();
    }

    void Window::init()
    {
        // Setup an error callback
        glfwSetErrorCallback([](int, const char* msg) { perror(msg); });

        // Initialize GLFW
        if (glfwInit() == GLFW_FALSE) {
            perror("Unable to init GLFW.");
            std::exit(EXIT_FAILURE);
        }

        if (width <= 0 || height <= 0) {
            glm::ivec2 res = getMaxResolution(glfwGetPrimaryMonitor());
            width = res.x;
            height = res.y;
        }

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
            perror("Failed to create GLFW window.");
            std::exit(EXIT_FAILURE);
        }
        // Make OpenGL context current
        glfwMakeContextCurrent(glfwWindow);

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            perror("Failed to init GLAD.");
            std::exit(EXIT_FAILURE);
        }

        // Set callbacks
        glfwSetFramebufferSizeCallback(glfwWindow, NULL);

        // Enable v-sync
        glfwSwapInterval(1);

        // Make the window visible
        glfwShowWindow(glfwWindow);

        glViewport(0, 0, width, height);
    }

    void Window::update(float dt)
    {
        float aspect = static_cast<float>(width) / static_cast<float>(height);
        Camera* camera = new PerspectiveCamera{{0.0f, 0.0f, 0.0f}, 0.1f, 10000.0f, aspect};
        Shader shader{"assets/shaders/vertex/vertex2D.glsl",
                      "assets/shaders/fragment/vertex2D.glsl"};
        shader.compile();
        BoxRenderer renderer{};
        renderer.start();
        Box box{glm::vec3{0.0f, 0.0f, -5.0f}, glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}};

        while (!glfwWindowShouldClose(glfwWindow)) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            camera->update(dt);
            renderer.add(box);
            renderer.render(camera, shader);

            glfwSwapBuffers(glfwWindow);
            glfwPollEvents();
        }

        delete camera;
    }

    void Window::destroy()
    {
        glfwSetErrorCallback(NULL);
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }

    void Window::setWindowSize(int newWidth, int newHeight)
    {
       // framebufferSizeCallback(glfwWindow, newWidth, newHeight);
    }

    void Window::setWindowTitle(const std::string& newTitle)
    {
        const char* str = newTitle.c_str();
        title = newTitle;
        glfwSetWindowTitle(glfwWindow, str);
    }

    std::string Window::getTitle() const noexcept
    {
        return title;
    }

    int Window::getWidth() const noexcept
    {
        return width;
    }


    int Window::getHeight() const noexcept
    {
        return height;
    }

}

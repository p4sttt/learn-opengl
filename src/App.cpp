#include "App.hpp"
#include "Logger.hpp"

void App::InitializeGLFW() {
    LOG_INFO("Initializing GLFW context");

    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
    } else {
        LOG_INFO("GLFW successfully initialized");
    }
}

App::Window::Window() : window(nullptr), renderer(nullptr) {
    LOG_INFO("Initializing GLFW context");

    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
    } else {
        LOG_INFO("GLFW successfully initialized");
    }

    LOG_INFO("Creating window without renderer");

    window = glfwCreateWindow(480, 480, "This is GLFW window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        LOG_ERROR("Failed to create window");
    } else {
        LOG_INFO("Window successfully created");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialize GLAD");
    } else {
        LOG_INFO("GLAD successfully initialized");
    }
}

App::Window::~Window() {
    LOG_INFO("Window has been successfully deleted");
    glfwDestroyWindow(window);
}

void App::Window::SetRenderer(Graphics::Renderer *renderer) {
    LOG_INFO("Setting renderer to window");
    this->renderer = renderer;
}

GLFWwindow *App::Window::GetGLFWwindow() { return window; }

void App::Window::Update() {}

void App::Window::Render() {
    glUseProgram((*renderer).GetShaderProgram().GetId());
    LOG_INFO("Starting renderer loop");

    while (!glfwWindowShouldClose(window)) {
        (*renderer).Render();
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
}

void App::EventHandler::FramebufferSizeCallback(GLFWwindow *window, int width,
                                                int height) {
    glViewport(0, 0, width, height);
}

void App::EventHandler::KeyCallback(GLFWwindow *window, int key, int scancode,
                                    int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void App::EventHandler::ErrorCallback(int error, const char *description) {
    LOG_ERROR("GL ERROR: " + std::to_string(error) + " " + description);
}

App::EventHandler::EventHandler(Window &window) : window(window) {

    glfwSetFramebufferSizeCallback(window.GetGLFWwindow(), FramebufferSizeCallback);
    glfwSetKeyCallback(window.GetGLFWwindow(), KeyCallback);
    glfwSetErrorCallback(ErrorCallback);
}

App::EventHandler::~EventHandler() {
    LOG_INFO("Event handler has been successfully deleted");
}

void App::EventHandler::HandleEvents() { glfwPollEvents(); }
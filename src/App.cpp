#include "App.hpp"
#include "Logger.hpp"

void App::InitializeGLFW() {
    LOG_INFO << "Initializing GLFW context" << '\n';

    if (!glfwInit()) {
        LOG_ERROR << "Failed to initialize GLFW" << '\n';
    } else {
        LOG_INFO << "GLFW successfully initialized" << '\n';
    }
}

App::Window::Window() : window(nullptr), renderer(nullptr) {
    LOG_INFO << "Initializing GLFW context" << '\n';

    if (!glfwInit()) {
        LOG_ERROR << "Failed to initialize GLFW" << '\n';
    } else {
        LOG_INFO << "GLFW successfully initialized" << '\n';
    }

    LOG_INFO << "Creating window without renderer" << '\n';

    window = glfwCreateWindow(480, 480, "This is GLFW window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        LOG_ERROR << "Failed to create window" << '\n';
    } else {
        LOG_INFO << "Window successfully created" << '\n';
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR << "Failed to initialize GLAD" << '\n';
    } else {
        LOG_INFO << "GLAD successfully initialized" << '\n';
    }
}

App::Window::~Window() {
    LOG_INFO << "Window has been successfully deleted" << '\n';
    glfwDestroyWindow(window);
}

void App::Window::SetRenderer(Graphics::Renderer *renderer) {
    LOG_INFO << "Setting renderer to window" << '\n';
    this->renderer = renderer;
}

GLFWwindow *App::Window::GetGLFWwindow() { return window; }

void App::Window::Update() {}

void App::Window::Render() {
    glUseProgram(renderer->GetShaderProgram().GetId());
    LOG_INFO << "Starting renderer loop" << '\n';

    while (!glfwWindowShouldClose(window)) {
        renderer->Render();
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
    LOG_ERROR << "GL ERROR: " << error << " " << description << '\n';
}

App::EventHandler::EventHandler(Window &window) : window(window) {

    glfwSetFramebufferSizeCallback(window.GetGLFWwindow(), FramebufferSizeCallback);
    glfwSetKeyCallback(window.GetGLFWwindow(), KeyCallback);
    glfwSetErrorCallback(ErrorCallback);
}

App::EventHandler::~EventHandler() {
    LOG_INFO << "Event handler has been successfully deleted" << '\n';
}

void App::EventHandler::HandleEvents() { glfwPollEvents(); }
#include "TransformController.hpp"
#include "Logger.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iterator>
#include "Window.hpp"

Window::Window() {
    LOG_INFO("Starting GLFW context");

    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
    } else {
        LOG_INFO("GLFW successfully initialized");
    }

    window = glfwCreateWindow(480, 480, "This is GLFW window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        LOG_ERROR("Failed to create window");
    } else {
        LOG_INFO("Window successfully created");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Failed to initialize GLAD");
    } else {
        LOG_INFO("GLAD successfully initialized");
    }
}

Window::~Window() { glfwTerminate(); }

void Window::setRenderer(OpenGLRenderer &renderer) {
    this->renderer = renderer;
}

void Window::Render() {
    LOG_INFO("Starting rendering loop");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.Render();
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void Window::FramebufferSizeCallback(GLFWwindow *window, int width,
                                     int height) {
    LOG_INFO("Window resized: height=" + std::to_string(height) +
             ", width=" + std::to_string(width));
    glViewport(0, 0, width, height);
}

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
    Window *instance = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        double angle = 0.05;
        switch (key) {
        case GLFW_KEY_UP:
            LOG("Rotation up: " +
                std::to_string(
                    instance->renderer.GetModels()[0].GetVertices()[2]));
            TransformController::Rotate(
                angle, Axis::x,
                instance->renderer.GetModels()[0].GetVertices());
            break;
        case GLFW_KEY_RIGHT:
            LOG("Rotation right: " +
                std::to_string(
                    instance->renderer.GetModels()[0].GetVertices()[0]));
            TransformController::Rotate(
                angle, Axis::y,
                instance->renderer.GetModels()[0].GetVertices());
            break;
        case GLFW_KEY_DOWN:
            LOG("Rotation down: " +
                std::to_string(
                    instance->renderer.GetModels()[0].GetVertices()[2]));
            TransformController::Rotate(
                -angle, Axis::x,
                instance->renderer.GetModels()[0].GetVertices());
            break;
        case GLFW_KEY_LEFT:
            LOG("Rotation left: " +
                std::to_string(
                    instance->renderer.GetModels()[0].GetVertices()[0]));
            TransformController::Rotate(
                -angle, Axis::y,
                instance->renderer.GetModels()[0].GetVertices());
            break;
        }
    }
}

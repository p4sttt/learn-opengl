#include "Logger.hpp"
#include <glad/glad.h>
#include "Window.hpp"
#include <iostream>

Window::Window() {
    LOG_INFO("Starting GLFW context");

    if (!glfwInit()) {
        LOG_ERROR("Failed to initialize GLFW");
    } else {
        LOG_INFO("GLFW successfully initialized");
    }

    window = glfwCreateWindow(640, 480, "This is GLFW window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        LOG_ERROR("Failed to create window");
    } else {
        LOG_INFO("Window successfully created");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
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
    LOG_INFO("Key pressed: " + std::to_string(key));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
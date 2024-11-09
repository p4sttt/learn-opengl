#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "glfw_utils.hpp"
#include "shader_utils.hpp"

constexpr unsigned int WIDTH = 640;
constexpr unsigned int HEIGHT = 480;

const std::string vertexShaderPath = "src/shader.vert";
const std::string fragmentShaderPath = "src/shader.frag";

int main() {
    GLFWwindow *window;

    if (!glfwInit()) {
        return -1;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "This is GLFW window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error: Failed to create window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // vertexies buffer object
    float positions[] = {
        0.3f, -0.3f,
        0.9f, 0.0f,
        0.1f, 0.1f,
        -0.4f, -0.5f,
        -0.1f, 0.3f,
        -0.8f, 0.0f
    };
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // elements buffer object
    unsigned int indices[] = {
        0, 1, 2,
        2, 0, 3,
        3, 2, 4,
        4, 3, 5
    };
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int progarm =
        LinkShaderProgram(vertexShaderPath, fragmentShaderPath);
    glUseProgram(progarm);

    const float timeStep = 0.01f; 
    float time = 0.0f;
    unsigned int timeLocation = glGetUniformLocation(progarm, "u_time");
    
    while (!glfwWindowShouldClose(window)) {
        glUniform1f(timeLocation, time);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        time += timeStep;
        glfwPollEvents();
    }

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(progarm);
    glfwTerminate();
    return 0;
}

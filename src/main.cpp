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

    // figure coordinates
    float triangle2d[] = {
        -0.5f,  0.5f,
         0.0f,  0.0f,
        -0.5f, -0.5f
    };
    float triangle3d[] = {
        0.5f,  0.5f, 0.0f,
        0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    // VBO - vertex buffer object
    // VAO - vertex array object
    unsigned int VBO[2], VAO[2];

    glGenBuffers(2, VBO);
    glGenVertexArrays(2, VAO);

    // settings for first VBO
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2d), triangle2d,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // settings for second VBO
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3d), triangle3d,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // unbind vertex array object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unsigned int shaderProgram =
        LinkShaderProgram(vertexShaderPath, fragmentShaderPath);
    glUseProgram(shaderProgram);

    const float timeStep = 0.01f;
    float time = 0.0f;
    unsigned int timeLocation = glGetUniformLocation(shaderProgram, "u_time");

    while (!glfwWindowShouldClose(window)) {
        glUniform1f(timeLocation, time);

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        time += timeStep;
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}

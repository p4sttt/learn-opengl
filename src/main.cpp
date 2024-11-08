#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertexies[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 0.0f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexies), vertexies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    unsigned int progarm =
        LinkShaderProgram(vertexShaderPath, fragmentShaderPath);
    glUseProgram(progarm);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteBuffers(1, &buffer);
    glDeleteProgram(progarm);
    glfwTerminate();
    return 0;
}

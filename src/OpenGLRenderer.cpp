#include "Logger.hpp"
#include "OpenGLRenderer.hpp"
#include <glad/glad.h>
#include <iostream>

OpenGLRenderer::OpenGLRenderer(const ShaderProgram &shaderProgram) {
    shaderProgramId = shaderProgram.GetShaderProgram();
    glUseProgram(shaderProgramId);
    timeAttribLocation = glGetUniformLocation(shaderProgramId, "u_time");
}

OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::addOpenGLModel(const OpenGLModel &model) {
    LOG_INFO("Adding model: " + std::to_string(model.getVertexArray()));
    models.push_back(model);
}

void OpenGLRenderer::Render() {
    glUniform1f(timeAttribLocation, time);

    for (OpenGLModel model : models) {
        glBindVertexArray(model.getVertexArray());
        glDrawElements(GL_TRIANGLES, model.getVerticesCount() * 3,
                       GL_UNSIGNED_INT, nullptr);
    }

    time += 0.01;
}
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

void OpenGLRenderer::AddOpenGLModel(const OpenGLModel &model) {
    LOG_INFO("Adding model: " + std::to_string(model.GetVertexArray()));
    models.push_back(model);
}

std::vector<OpenGLModel> &OpenGLRenderer::GetModels() { return models; }

void OpenGLRenderer::Render() {
    glUniform1f(timeAttribLocation, time);

    for (OpenGLModel model : models) {
        model.UpdateVertices();
        glBindVertexArray(model.GetVertexArray());
        glDrawElements(GL_LINES, model.GetVerticesCount() * 3, GL_UNSIGNED_INT,
                       nullptr);
    }

    time += 0.01;
}
#include "Logger.hpp"
#include "OpenGLModel.hpp"
#include <glad/glad.h>
#include <iostream>

OpenGLModel::OpenGLModel(const std::vector<float> &vertices,
                         const std::vector<unsigned int> &indices)
    : vertices(vertices), indices(indices) {
    LOG_INFO("Creating OpenGLModel with vertices: " +
             std::to_string(vertices.size()) +
             ", indices: " + std::to_string(indices.size()));

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    LOG_INFO("Initialize VBO, EBO, VAO: " + std::to_string(VBO) + ", " +
             std::to_string(EBO) + ", " + std::to_string(VAO));

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
};

OpenGLModel::~OpenGLModel() {}

void OpenGLModel::UpdateVertices() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::vector<float> &OpenGLModel::GetVertices() { return vertices; }

const unsigned int OpenGLModel::GetVertexArray() const { return VAO; }

const unsigned int OpenGLModel::GetVerticesCount() const {
    return vertices.size();
}
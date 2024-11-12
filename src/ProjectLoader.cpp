#include "Logger.hpp"
#include "ProjectLoader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

void ProjectLoader::loadModel(const std::string &modelPath,
                              OpenGLModel &model) {
    LOG_INFO("Starting loading model: " + modelPath);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    std::fstream modelFile(modelPath);

    if (!modelFile.is_open()) {
        LOG_ERROR("Failed to open model file: " + modelPath);
        throw std::runtime_error("Failed to open model file");
    }

    std::string line;
    while (std::getline(modelFile, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.front() == 'v') {
            LOG_INFO("Starting parsing vertex: " + line);
            std::vector<float> currentVertex;
            parseVertex(line, currentVertex);
            LOG("Parsed vertex: " + std::to_string(currentVertex[0]) + ", " +
                std::to_string(currentVertex[1]) + ", " +
                std::to_string(currentVertex[2]));
            vertices.insert(vertices.end(), currentVertex.begin(),
                            currentVertex.end());
        } else if (line.front() == 'f') {
            LOG_INFO("Starting parsing indices: " + line);
            parseIndices(line, indices);
            LOG("First parsed indices: " + std::to_string(indices[0]) + ", " +
                std::to_string(indices[1]) + ", " + std::to_string(indices[2]));
        }
    }

    LOG_INFO("Finished loading model: " + modelPath);

    modelFile.close();

    model = OpenGLModel(vertices, indices);

    LOG("Model vertices: " + std::to_string(model.getVerticesCount()));
}

void ProjectLoader::loadShaderProgram(const std::string &vertexShaderPath,
                                      const std::string &fragmentShaderPath,
                                      ShaderProgram &shaderProgram) {
    LOG_INFO("Starting loading shader program");

    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    loadShader(vertexShaderPath, vertexShaderSource);
    loadShader(fragmentShaderPath, fragmentShaderSource);

    LOG_INFO("Vertex shader source:\n" + vertexShaderSource);
    LOG_INFO("Fragment shader source: \n" + fragmentShaderSource);

    LOG_INFO("Finished loading shader program");

    shaderProgram = ShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void ProjectLoader::loadShader(const std::string &vertexShaderPath,
                               std::string &vertexShaderSource) {

    LOG("Starting Loading shader: " + vertexShaderPath);
    std::stringstream shader;
    std::ifstream stream(vertexShaderPath);

    std::string line;
    while (std::getline(stream, line)) {
        shader << line << "\n";
    }

    LOG_INFO("Finished loading shader: " + vertexShaderPath);

    vertexShaderSource = shader.str();
}

void ProjectLoader::parseVertex(const std::string &line,
                                std::vector<float> &vertices) {
    std::stringstream ss(line);
    std::string vertexType;
    ss >> vertexType;

    if (vertexType != "v") {
        LOG_ERROR("Invalid vertex type: " + vertexType);
        throw std::runtime_error("Invalid vertex type");
    }

    float vertex;
    while (ss >> vertex) {
        vertices.push_back(vertex);
    }
}

void ProjectLoader::parseIndices(const std::string &line,
                                 std::vector<unsigned int> &indices) {
    std::stringstream ss(line);
    std::string indexType;
    ss >> indexType;

    if (indexType != "f") {
        LOG_ERROR("Invalid index type: " + indexType);
        throw std::runtime_error("Invalid index type");
    }

    unsigned int index;
    while (ss >> index) {
        indices.push_back(index);
    }
}
#include <glad/glad.h>
#include "ProjectLoader.hpp"
#include "Logger.hpp"
#include <fstream>
#include <sstream>

ProjectLoader *ProjectLoader::instance = nullptr;

ProjectLoader::ProjectLoader() { LOG_INFO("ProjectLoader was created"); }

ProjectLoader &ProjectLoader::GetInstance() {
    if (instance == nullptr) {
        instance = new ProjectLoader();
    }
    return *instance;
}

void ProjectLoader::ParseVertex(const std::string line, Math::Vertex &vertex) {
    std::stringstream ss(line);
    std::string vertexType;
    ss >> vertexType;

    if (vertexType != "v") {
        LOG_ERROR("Invalid vertex type: " + vertexType);
        throw std::runtime_error("Invalid vertex type");
    }

    ss >> vertex.x;
    ss >> vertex.y;
    ss >> vertex.z;
}

void ProjectLoader::ParseIndices(const std::string line,
                                 std::vector<unsigned int> &indices) {
    std::stringstream ss(line);
    std::string indicesType;
    ss >> indicesType;

    if (indicesType != "f") {
        LOG_ERROR("Invalid indices type: " + indicesType);
        throw std::runtime_error("Invalid indices type");
    }

    unsigned int index;
    while (ss >> index) {
        indices.push_back(index);
    }
}

Graphics::Model ProjectLoader::LoadModel() {
    LOG_INFO("Starting loading model: " + modelPath);

    std::vector<Math::Vertex> vertices;
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

            Math::Vertex currentVertex;
            ParseVertex(line, currentVertex);

            LOG("Parsed vertex: x=" + std::to_string(currentVertex.x) +
                ", y=" + std::to_string(currentVertex.y) +
                ", z=" + std::to_string(currentVertex.z));

            vertices.push_back(currentVertex);
        } else if (line.front() == 'f') {
            LOG_INFO("Starting parsing indices: " + line);
            ParseIndices(line, indices);
            LOG_INFO("Indices has been successfully parsed");
        }
    }

    LOG("Model has been successfully parsed\nVertices count: " +
        std::to_string(vertices.size()) +
        ", Indices count: " + std::to_string(indices.size()));
    modelFile.close();

    return Graphics::Model(GL_LINES, vertices, indices);
}

void ProjectLoader::LoadShader(const std::string &shaderPath,
                               std::string &shaderSource) {
    LOG("Starting Loading shader: " + shaderPath);
    std::stringstream shader;
    std::ifstream stream(shaderPath);

    std::string line;
    while (std::getline(stream, line)) {
        shader << line << "\n";
    }

    LOG_INFO("Finished loading shader: " + shaderPath);
    LOG_INFO("Shader source: " + shader.str());

    shaderSource = shader.str();
}

Graphics::ShaderProgram ProjectLoader::LoadShaderProgram() {
    LOG_INFO("Starting loading shader program");

    std::string vertexShaderSource, fragmentShaderSource;

    LoadShader(vertexShaderPath, vertexShaderSource);
    LoadShader(fragmentShaderPath, fragmentShaderSource);

    return Graphics::ShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void ProjectLoader::SetVertexShaderPath(const std::string &path) {
    LOG_INFO("Setting vertex shader path: " + path);
    vertexShaderPath = path;
}

void ProjectLoader::SetFragmentShaderPath(const std::string &path) {
    LOG_INFO("Setting fragment shader path: " + path);
    fragmentShaderPath = path;
}

void ProjectLoader::SetModelPath(const std::string &path) {
    LOG_INFO("Setting model path: " + path);
    modelPath = path;
}

const std::string &ProjectLoader::GetVertexShaderPath() const {
    return vertexShaderPath;
}

const std::string &ProjectLoader::GetFragmentShaderPath() const {
    return fragmentShaderPath;
}

const std::string &ProjectLoader::GetModelPath() const { return modelPath; }

#include <glad/glad.h>
#include "ProjectLoader.hpp"
#include "Logger.hpp"
#include <fstream>
#include <sstream>

ProjectLoader *ProjectLoader::instance = nullptr;

ProjectLoader::ProjectLoader() { LOG_INFO << "ProjectLoader was created" << '\n'; }

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
        LOG_ERROR << "Invalid vertex type: " + vertexType << '\n';
        throw std::runtime_error("Invalid vertex type");
    }

    ss >> vertex.x >> vertex.y >> vertex.z;
}

void ProjectLoader::ParseIndices(const std::string line,
                                 std::vector<unsigned> &indices) {
    std::stringstream ss(line);
    std::string indicesType;
    ss >> indicesType;

    if (indicesType != "f") {
        LOG_ERROR << "Invalid indices type: " << indicesType << '\n';
        throw std::runtime_error("Invalid indices type");
    }

    unsigned index;
    while (ss >> index) {
        indices.push_back(index);
    }
}

Graphics::Model ProjectLoader::LoadModel() {
    LOG_INFO << "Starting loading model: " << modelPath << '\n';

    std::vector<Math::Vertex> vertices;
    std::vector<unsigned> indices;

    std::fstream modelFile(modelPath);

    if (!modelFile.is_open()) {
        LOG_ERROR << "Failed to open model file: " << modelPath << '\n';
        throw std::runtime_error("Failed to open model file");
    }

    std::string line;
    while (std::getline(modelFile, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.front() == 'v') {
            LOG_INFO << "Starting parsing vertex: " << line << '\n';

            Math::Vertex currentVertex;
            ParseVertex(line, currentVertex);

            LOG << "Parsed vertex: x=" << currentVertex.x  << ", y=" << currentVertex.y
                << ", z=" << currentVertex.z;

            vertices.push_back(currentVertex);
        } else if (line.front() == 'f') {
            LOG_INFO << "Starting parsing indices: " << line << '\n';
            ParseIndices(line, indices);
            LOG_INFO << "Indices has been successfully parsed" << '\n';
        }
    }

    LOG << "Model has been successfully parsed\nVertices count: " << vertices.size()
        <<  ", Indices count: " << indices.size();
    modelFile.close();

    return Graphics::Model(GL_LINES, vertices, indices);
}

void ProjectLoader::LoadShader(const std::string &shaderPath,
                               std::string &shaderSource) {
    LOG << "Starting Loading shader: " << shaderPath << '\n';
    std::stringstream shader;
    std::ifstream stream(shaderPath);

    std::string line;
    while (std::getline(stream, line)) {
        shader << line << "\n";
    }

    LOG_INFO << "Finished loading shader: " << shaderPath << '\n';
    LOG_INFO << "Shader source: " << shader.str() << '\n';

    shaderSource = shader.str();
}

Graphics::ShaderProgram ProjectLoader::LoadShaderProgram() {
    LOG_INFO << "Starting loading shader program" << '\n';

    std::string vertexShaderSource, fragmentShaderSource;

    LoadShader(vertexShaderPath, vertexShaderSource);
    LoadShader(fragmentShaderPath, fragmentShaderSource);

    return Graphics::ShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void ProjectLoader::SetVertexShaderPath(const std::string &path) {
    LOG_INFO << "Setting vertex shader path: " << path << '\n';
    vertexShaderPath = path;
}

void ProjectLoader::SetFragmentShaderPath(const std::string &path) {
    LOG_INFO << "Setting fragment shader path: " << path << '\n';
    fragmentShaderPath = path;
}

void ProjectLoader::SetModelPath(const std::string &path) {
    LOG_INFO << "Setting model path: " << path << '\n';
    modelPath = path;
}

const std::string &ProjectLoader::GetVertexShaderPath() const {
    return vertexShaderPath;
}

const std::string &ProjectLoader::GetFragmentShaderPath() const {
    return fragmentShaderPath;
}

const std::string &ProjectLoader::GetModelPath() const { return modelPath; }

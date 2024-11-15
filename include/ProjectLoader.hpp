#pragma once

#include "Graphics.hpp"
#include <string>

class ProjectLoader {
  private:
    static ProjectLoader *instance;

    std::string vertexShaderPath = "res/vertex.glsl";
    std::string fragmentShaderPath = "res/fragment.glsl";
    std::string modelPath = "res/model.obj";

    ProjectLoader();
    ProjectLoader(const ProjectLoader &) = delete;
    ProjectLoader &operator=(const ProjectLoader &) = delete;
    ~ProjectLoader() = default;

    void ParseVertex(const std::string line, Math::Vertex &vertex);
    void ParseIndices(const std::string line, std::vector<unsigned> &indices);
    void LoadShader(const std::string &shaderPath, std::string &shaderSource);

  public:
    static ProjectLoader &GetInstance();

    Graphics::Model LoadModel();
    Graphics::ShaderProgram LoadShaderProgram();

    void SetVertexShaderPath(const std::string &path);
    void SetFragmentShaderPath(const std::string &path);
    void SetModelPath(const std::string &path);

    const std::string &GetVertexShaderPath() const;
    const std::string &GetFragmentShaderPath() const;
    const std::string &GetModelPath() const;
};
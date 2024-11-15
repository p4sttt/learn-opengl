#pragma once

#include "Graphics.hpp"
#include <string>

class ProjectLoader {
  private:
    static ProjectLoader *instance;

    const char *vertexShaderPath = "res/vertex.glsl";
    const char *fragmentShaderPath = "res/fragment.glsl";
    const char *modelPath = "res/model.obj";

    ProjectLoader();
    ProjectLoader(const ProjectLoader &) = delete;
    ProjectLoader &operator=(const ProjectLoader &) = delete;
    ~ProjectLoader() = default;

    void ParseVertex(const std::string line, Math::Vertex &vertex);
    void ParseIndices(const std::string line, std::vector<unsigned> &indices);
    void LoadShader(const char *shaderPath, std::string &shaderSource);

  public:
    static ProjectLoader &GetInstance();

    Graphics::Model LoadModel();
    Graphics::ShaderProgram LoadShaderProgram();

    void SetVertexShaderPath(const char *path);
    void SetFragmentShaderPath(const char *path);
    void SetModelPath(const char *path);

    const char *GetVertexShaderPath() const;
    const char *GetFragmentShaderPath() const;
    const char *GetModelPath() const;
};
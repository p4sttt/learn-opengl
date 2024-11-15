#pragma once

#include <vector>
#include <string>
#include "Math.hpp"

namespace Graphics {

class Buffer {
  private:
    unsigned int id;
    unsigned int type;

  public:
    Buffer();
    Buffer(const void *data, unsigned int size, unsigned int type);
    ~Buffer();

    void Bind() const;
    void Unbind() const;

    unsigned int GetId() const { return id; }
};

class VertexArray {
  private:
    unsigned int id;

  public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const Buffer &buffer, unsigned int index);
};

class ShaderProgram {
  private:
    unsigned int id;
    unsigned int CompileShader(unsigned int type, const std::string &source);

  public:
    ShaderProgram(const std::string &vertexShaderSource,
                  const std::string &fragmentShaderSource);
    ~ShaderProgram();

    unsigned int GetId() const;
};

class Model {
  private:
    unsigned int renderType;
    std::vector<Math::Vertex> vertices;
    std::vector<unsigned int> indices;

    VertexArray vao;
    Buffer vbo, ebo;

  public:
    Model(unsigned int mode, const std::vector<Math::Vertex> &vertices,
          const std::vector<unsigned int> &indices);
    ~Model();

    void UpdateVertices();

    std::vector<Math::Vertex> &GetVertices();
    size_t GetVerticesCount();
    Buffer &GetVertexBuffer();
    Buffer &GetElementsBuffer();
    VertexArray &GetVertexArray();
    unsigned GetRendererType() const;
};

class Renderer {
  private:
    Model model;
    ShaderProgram shaderProgram;
    float time = 0.0f;
    float timeStep = 0.01f;

  public:
    Renderer(Graphics::Model &model, Graphics::ShaderProgram &shaderProgram);
    ~Renderer();

    Model &GetModel();
    ShaderProgram &GetShaderProgram();

    void Render();
};

} // namespace Graphics
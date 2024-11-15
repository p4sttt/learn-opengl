#pragma once

#include <vector>
#include <string>
#include "Math.hpp"

namespace Graphics {

class Buffer {
  private:
    unsigned id;
    unsigned type;

  public:
    Buffer();
    Buffer(const void *data, unsigned size, unsigned type);
    ~Buffer();

    void Bind() const;
    void Unbind() const;

    unsigned GetId() const { return id; }
};

class VertexArray {
  private:
    unsigned id;

  public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const Buffer &buffer, unsigned index);
};

class ShaderProgram {
  private:
    unsigned id;
    unsigned CompileShader(unsigned type, const char *source);

  public:
    ShaderProgram(const char *vertexShaderSource,
                  const char *fragmentShaderSource);
    ~ShaderProgram();

    unsigned GetId() const;
};

class Model {
  private:
    unsigned renderType;
    std::vector<Math::Vertex> vertices;
    std::vector<unsigned> indices;

    VertexArray vao;
    Buffer vbo, ebo;

  public:
    Model(unsigned mode, const std::vector<Math::Vertex> &vertices,
          const std::vector<unsigned> &indices);
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
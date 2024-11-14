#include "Graphics.hpp"
#include <glad/glad.h>
#include "Logger.hpp"
#include <iostream>

Graphics::Buffer::Buffer() : type(0) {
    LOG_INFO("Create empty buffer");
    glGenBuffers(1, &id);
}

Graphics::Buffer::Buffer(const void *data, unsigned int size, unsigned int type)
    : type(type) {
    LOG_INFO("Creating buffer: " + std::to_string(type) +
             ", size: " + std::to_string(size));
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, size * sizeof(float), data, GL_STATIC_DRAW);
}

Graphics::Buffer::~Buffer() { glDeleteBuffers(1, &id); }

void Graphics::Buffer::Bind() const { glBindBuffer(type, id); }

void Graphics::Buffer::Unbind() const { glBindBuffer(type, 0); }

Graphics::VertexArray::VertexArray() {
    LOG_INFO("Creating vertex array");
    glGenVertexArrays(1, &id);
}

Graphics::VertexArray::~VertexArray() { glDeleteVertexArrays(1, &id); }

void Graphics::VertexArray::Bind() const { glBindVertexArray(id); }

void Graphics::VertexArray::Unbind() const { glBindVertexArray(0); }

void Graphics::VertexArray::AddBuffer(const Buffer &buffer, unsigned int index) {
    Bind();
    buffer.Bind();

    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(index);

    buffer.Unbind();
    Unbind();
}

unsigned int Graphics::ShaderProgram::CompileShader(unsigned int type,
                                                    const std::string &source) {
    unsigned int shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG_ERROR("Shader compilation failed: " + std::string(infoLog));
    }

    return shader;
}

Graphics::ShaderProgram::ShaderProgram(const std::string &vertexShaderSource,
                                       const std::string &fragmentShaderSource) {
    LOG_INFO("Creating shader program");

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader =
        CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        LOG_ERROR("Shader program linking failed: " + std::string(infoLog));
    }

    LOG_INFO("Shader program created");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Graphics::ShaderProgram::~ShaderProgram() { glDeleteProgram(id); }

unsigned int Graphics::ShaderProgram::GetId() const { return id; }

Graphics::Model::Model(unsigned int renderType,
                       const std::vector<Math::Vertex> &vertices,
                       const std::vector<unsigned int> &indices)
    : renderType(renderType), vertices(vertices), indices(indices),
      vbo(vertices.data(), vertices.size() * sizeof(Math::Vertex), GL_ARRAY_BUFFER),
      ebo(indices.data(), indices.size() * sizeof(unsigned int),
          GL_ELEMENT_ARRAY_BUFFER),
      vao() {

    LOG_INFO("Creating model: " + std::to_string(renderType) +
             ", vertices count: " + std::to_string(vertices.size()) +
             ", indices count: " + std::to_string(indices.size()));

    vao.Bind();
    vao.AddBuffer(vbo, 0);
    vao.Unbind();
}

Graphics::Model::~Model() {
    vao.~VertexArray();
    vbo.~Buffer();
    ebo.~Buffer();
}

void Graphics::Model::UpdateVertices() {
    vbo.~Buffer();
    vbo = Buffer(vertices.data(), vertices.size() * sizeof(Math::Vertex),
                 GL_ARRAY_BUFFER);
}

std::vector<Math::Vertex> &Graphics::Model::GetVertices() { return vertices; }

size_t Graphics::Model::GetVerticesCount() { return vertices.size(); }

Graphics::Buffer &Graphics::Model::GetVertexBuffer() { return vbo; }

Graphics::Buffer &Graphics::Model::GetElementsBuffer() { return ebo; }

Graphics::VertexArray &Graphics::Model::GetVertexArray() { return vao; }

const unsigned int &Graphics::Model::GetRendererType() const { return renderType; }

Graphics::Renderer::Renderer(Graphics::Model &model,
                             Graphics::ShaderProgram &shaderProgram)
    : model(model), shaderProgram(shaderProgram) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

Graphics::Renderer::~Renderer() {}

Graphics::Model &Graphics::Renderer::GetModel() { return model; }

Graphics::ShaderProgram &Graphics::Renderer::GetShaderProgram() {
    return shaderProgram;
}

void Graphics::Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    unsigned int uniformTimeLocation =
        glGetUniformLocation(shaderProgram.GetId(), "u_time");
    glUniform1f(uniformTimeLocation, time);

    model.GetVertexArray().Bind();
    model.GetElementsBuffer().Bind();
    model.GetVertexBuffer().Bind();
    glDrawArrays(model.GetRendererType(), 0, model.GetVerticesCount());
    model.GetVertexArray().Unbind();

    time += timeStep;
}
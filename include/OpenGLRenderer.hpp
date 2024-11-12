#include "OpenGLModel.hpp"
#include "ShaderProgram.hpp"

#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

class OpenGLRenderer {
  private:
    std::vector<OpenGLModel> models;
    unsigned int shaderProgramId, timeAttribLocation;
    float time = 0.0f;

  public:
    OpenGLRenderer() {}
    OpenGLRenderer(const ShaderProgram &shaderProgram);
    ~OpenGLRenderer();

    void addOpenGLModel(const OpenGLModel &model);

    void Render();
};

#endif
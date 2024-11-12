#include "ShaderProgram.hpp"
#include "OpenGLModel.hpp"

#ifndef PROJECT_LOADER_HPP
#define PROJECT_LOADER_HPP

class ProjectLoader {
  private:
    static void parseVertex(const std::string &line,
                            std::vector<float> &vertices);
    static void parseIndices(const std::string &line,
                             std::vector<unsigned int> &indices);
    static void loadShader(const std::string &vertexShaderPath,
                           std::string &vertexShaderSource);

  public:
    static void loadModel(const std::string &modelPath, OpenGLModel &model);
    static void loadShaderProgram(const std::string &vertexShaderPath,
                                  const std::string &fragmentShaderPath,
                                  ShaderProgram &shaderProgram);
};

#endif

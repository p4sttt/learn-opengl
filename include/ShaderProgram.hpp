#include <string>

#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

class ShaderProgram {
  private:
    unsigned int id;
    unsigned int CompileShader(unsigned int type, const std::string &source);

  public:
    ShaderProgram() {}
    ShaderProgram(const std::string &vertexShaderSource,
                  const std::string &fragmentShaderSource);
    ~ShaderProgram();

    unsigned int GetShaderProgram() const;
};

#endif

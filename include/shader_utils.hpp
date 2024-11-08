#ifndef SHADER_UTILS_HPP
#define SHADER_UTILS_HPP

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

void ParseShader(const std::string &path, std::string &out);
unsigned int CompileShader(unsigned int type, const std::string &source);
unsigned int LinkShaderProgram(const std::string &vertexShaderPath,
                               const std::string &fragmentShaderPath);

#endif

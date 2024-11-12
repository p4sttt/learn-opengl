#include "Logger.hpp"
#include "ShaderProgram.hpp"
#include <glad/glad.h>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string &vertexShaderSource,
                             const std::string &fragmentShaderSource) {
    LOG_INFO("Start initializing shader program");
    id = glCreateProgram();

    LOG("Initialize shader program: " + std::to_string(id));

    unsigned int vertexShader =
        ShaderProgram::CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader =
        ShaderProgram::CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    LOG_INFO("Start linkig shaders");
    LOG("Initialize Vertex shader: " + std::to_string(vertexShader));
    LOG("Initialize Fragment shader: " + std::to_string(fragmentShader));

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        char *logMessage = new char[length];
        glGetProgramInfoLog(id, length, &length, logMessage);
        LOG_ERROR("Linkn program failed:\n" + std::string(logMessage));
    } else {
        LOG_INFO("Shaders were successfully linked");
    }
}

ShaderProgram::~ShaderProgram() {}

unsigned int ShaderProgram::CompileShader(unsigned int type,
                                          const std::string &source) {
    LOG_INFO("Start compiling shader: " + std::to_string(type));
    unsigned int id = glCreateShader(type);

    LOG("Initialize shader: " + std::to_string(id));

    const char *sourceCharArray = source.c_str();
    glShaderSource(id, 1, &sourceCharArray, NULL);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *logMessage = new char[length];
        glGetShaderInfoLog(id, length, &length, logMessage);
        LOG_ERROR("Compile shader failed:\n" + std::string(logMessage));
        glDeleteShader(id);
        return 0;
    } else {
        LOG_INFO("Shader was successfully compiled");
        return id;
    }
}

unsigned int ShaderProgram::GetShaderProgram() const { return id; }
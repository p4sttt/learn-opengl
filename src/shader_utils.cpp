#include "shader_utils.hpp"

void ParseShader(const std::string &path, std::string &out) {
    std::stringstream shader;
    std::ifstream stream(path);

    std::string line;
    while (std::getline(stream, line)) {
        shader << line << "\n";
    }

    out = shader.str();
}

unsigned int CompileShader(unsigned int type, const std::string &source) {
    unsigned int id = glCreateShader(type);
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
        std::cout << "Error: Compile shader failed" << std::endl;
        std::cout << logMessage << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int LinkShaderProgram(const std::string &vertexShaderPath,
                               const std::string &fragmentShaderPath) {
    unsigned int id = glCreateProgram();

    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    ParseShader(vertexShaderPath, vertexShaderSource);
    ParseShader(fragmentShaderPath, fragmentShaderSource);

    unsigned int vertexShader =
        CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader =
        CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

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
        std::cout << "Error: Linkn program failed" << std::endl;
        std::cout << logMessage << std::endl;
        return 0;
    }

    return id;
}

#include <vector>

#ifndef OPENGL_MODEL_HPP
#define OPENGL_MODEL_HPP

class OpenGLModel {
  private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int VBO, EBO, VAO;

  public:
    OpenGLModel() {};
    OpenGLModel(const std::vector<float> &vertices,
                const std::vector<unsigned int> &indices);
    ~OpenGLModel();

    void UpdateVertices();
    std::vector<float> &GetVertices();
    const unsigned int GetVertexArray() const;
    const unsigned int GetVerticesCount() const;
};

#endif

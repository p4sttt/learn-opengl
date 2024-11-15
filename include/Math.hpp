#pragma once

#include <vector>

namespace Math {

struct Vertex {
    float x, y, z;
};

enum Axis { x, y, z };

class Matrix {
  private:
    std::vector<float> data = {};
    int rows = 0, cols = 0;

  public:
    Matrix(int rows, int cols);
    Matrix operator*(const Matrix &other) const;
    Matrix operator+(const Matrix &other) const;
    float &operator()(int row, int col);
    const float &operator()(int row, int col) const;
};

class TransformController {};

} // namespace Math
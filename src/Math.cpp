#include "Math.hpp"

Math::Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    data.resize(rows * cols);
}

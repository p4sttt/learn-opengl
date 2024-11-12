#include "TransformController.hpp"
#include "Logger.hpp"
#include <cmath>
#include <cstddef>
#include <string>

void TransformController::Move(double distance, Axis axis,
                               std::vector<float> &vertices) {
    std::size_t verticesCount = vertices.size();

    if (verticesCount % 3) {
        LOG("Bad vertices count: " + std::to_string(verticesCount));
    }

    for (std::size_t i = 0; i < verticesCount; i += 3) {
        vertices[i + axis] += static_cast<float>(distance);
    }
}

void TransformController::Rotate(double angle, Axis axis,
                                 std::vector<float> &vertices) {
    std::size_t verticesCount = vertices.size();

    if (verticesCount % 3) {
        LOG("Bad vertices count: " + std::to_string(verticesCount));
    }

    switch (axis) {
    case x: {
        for (std::size_t i = 0; i < verticesCount; i += 3) {
            float y = vertices[i + 1];
            float z = vertices[i + 2];
            vertices[i + 1] = cos(angle) * y - sin(angle) * z;
            vertices[i + 2] = sin(angle) * y + cos(angle) * z;
        }
        break;
    }
    case y: {
        for (std::size_t i = 0; i < verticesCount; i += 3) {
            float x = vertices[i];
            float z = vertices[i + 2];
            vertices[i] = cos(angle) * x - sin(angle) * z;
            vertices[i + 2] = sin(angle) * x + cos(angle) * z;
        }
        break;
    }
    case z: {
        for (std::size_t i = 0; i < verticesCount; i += 3) {
            float x = vertices[i];
            float y = vertices[i + 2];
            vertices[i] = cos(angle) * x - sin(angle) * y;
            vertices[i + 2] = sin(angle) * x + cos(angle) * y;
        }
        break;
    }
    default:
        LOG_ERROR("Incorrect axis value: " + std::to_string(axis));
    }
}

void TransformController::Zoom(double n, std::vector<float> &vertices) {
    std::size_t verticesCount = vertices.size();
    
    if (!(verticesCount % 3)) {
        LOG("Bad vertices count: " + std::to_string(verticesCount));
    }

    for (std::size_t i = 0; i < verticesCount; i += 3) {
        vertices[i] *= static_cast<float>(n);
        vertices[i + 1] *= static_cast<float>(n);
        vertices[i + 2] *= static_cast<float>(n);
    }
}

#include <vector>

#ifndef TRANSFORM_CONTROLLER_HPP
#define TRANSFORM_CONTROLLER_HPP

enum Axis { x, y, z };

class TransformController {
  public:
    static void Move(double distance, Axis axis, std::vector<float> &vertices);
    static void Rotate(double angle, Axis axis, std::vector<float> &vertices);
    static void Zoom(double n, std::vector<float> &vertices);
};

#endif

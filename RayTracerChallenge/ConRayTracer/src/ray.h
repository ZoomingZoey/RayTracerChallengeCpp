#pragma once

#include <vector>
#include "sphere.h"
#include "point.h"
#include "vector.h"
#include "intersection.h"
#include "matrix4.h"
#include "world.h"

class Ray {
 public:
  Ray(const Point& origin, const Vector& direction);
  Point GetOrigin() const;
  Vector GetDirection() const;
  Point position(float time) const;
  std::vector<float> intersect(const Sphere& sphere) const;
  std::vector<Intersection> intersect(const World& world) const;
  Ray transform(const Matrix4& matrix) const;
 private:
  Point origin_;
  Vector direction_;
};

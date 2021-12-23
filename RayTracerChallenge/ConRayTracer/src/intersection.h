#pragma once

#include <vector>
#include "mesh.h"

class Intersection {
 public:
  Intersection();
  Intersection(float time, Mesh* object);
  Intersection(const Intersection& other);
  ~Intersection();
  float GetTime() const;
  void SetTime(float time);
  Mesh* GetObject() const;
  void SetObject(Mesh* object);
  bool operator==(const Intersection& other) const;
  Intersection& operator=(const Intersection& other);
  static void swap(Intersection& a, Intersection& b);
  static std::vector<Intersection> intersections(const std::vector<Intersection>& intersections);
 private:
  float time_;
  Mesh* mesh_object_;
};

#pragma once

#include "object.h"
#include "material.h"
#include "vector.h"
#include "point.h"

class Mesh : public Object {
 public:
  Mesh(std::string name, const ObjectType& type);
  Mesh(std::string name, const ObjectType& type, const Matrix4& transform);
  Mesh(std::string name, const ObjectType& type, const Material& material);
  Mesh(std::string name, const ObjectType& type, const Material& material,
                                               const Matrix4& transform);
  virtual ~Mesh();
  void ListDetails() const override;
  Vector normal_at(const Point& world_point) const;
  Material GetMaterial() const;
  void SetMaterial(const Material& material);
  static int GetCount();
  bool operator==(const Object& object) const override;
  Mesh& operator=(const Object& other) override;
 private:
  static int mesh_count_;
  Material material_;
};
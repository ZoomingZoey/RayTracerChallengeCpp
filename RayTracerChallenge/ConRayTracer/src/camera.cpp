#include "camera.h"

int Camera::camera_count_ = 0;

struct CanvasData {
  float half_width = NULL;
  float half_height = NULL;
  float pixel_size = NULL;
};

CanvasData CalculateCanvasData(int hsize, int vsize, float field_of_view) {
  CanvasData data;
  float half_view = tan(field_of_view / 2);
  float aspect = ((float)hsize) / vsize;

  if (aspect >= 1) {
    data.half_width = half_view;
    data.half_height = half_view / aspect;
  }
  if (aspect < 1) {
    data.half_height = half_view;
    data.half_width = half_view * aspect;
  }

  float full_width = data.half_width * 2;
  data.pixel_size = full_width / hsize;

  return data;
}

Camera::Camera(const std::string& name, int hsize, int vsize, float field_of_view)
  : hsize_(hsize), vsize_(vsize),
    field_of_view_(field_of_view),
    Object(name, ObjectType::kCamera) {
  camera_count_++;
  
  CanvasData data = CalculateCanvasData(hsize_, vsize_, field_of_view_);
  pixel_size_ = data.pixel_size;
  half_width_ = data.half_width;
  half_height_ = data.half_height;
}

Camera::Camera(const std::string& name, int hsize, int vsize, float field_of_view,
                                                       const Matrix4& transform)
  : hsize_(hsize), vsize_(vsize),
    field_of_view_(field_of_view),
    Object(name, ObjectType::kCamera, transform) {
  camera_count_++;
  
  CanvasData data = CalculateCanvasData(hsize_, vsize_, field_of_view_);
  pixel_size_ = data.pixel_size;
  half_width_ = data.half_width;
  half_height_ = data.half_height;
}

Camera::~Camera() { camera_count_--; }

int Camera::GetHorizontalSize() const { return hsize_; }
void Camera::SetHorizontalSize(int hsize) { hsize_ = hsize; }
int Camera::GetVerticalSize() const { return vsize_; }
void Camera::SetVerticalSize(int vsize) { vsize_ = vsize; }
float Camera::GetFieldOfView() const { return (float)field_of_view_; }
void Camera::SetFieldOfView(double field_of_view) {
  field_of_view_ = field_of_view;
}
float Camera::GetPixelSize() const { return pixel_size_; }
float Camera::GetHalfWidth() const { return half_width_; }
float Camera::GetHalfHeight() const { return half_height_; }

void Camera::ListDetails() const {
  std::string parent_name = parent_ == nullptr ? "None" : parent_->GetName();
  std::cout << "Name: " << name_ << "\n"
    << "Type: " << this->GetObjectTypeName() << "\n"
    << "ID: " << id_ << "\n"
    << "Transform:\n" << transform_.format()
    << "Parent: " << parent_name << "\n"
    << "Horizontal Size: " << hsize_ << "\n"
    << "Vertical Size: " << vsize_ << "\n"
    << "Field of view: " << field_of_view_ << "\n";
}

int Camera::GetCount() {
  return camera_count_;
}

bool Camera::operator==(const Object& object) const {
  Camera* other = (Camera*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    parent_ == other->GetParent() &&
    id_ == other->GetID() &&
    hsize_ == other->GetHorizontalSize() &&
    vsize_ == other->GetVerticalSize() &&
    utils::equal(field_of_view_, other->GetFieldOfView()));
}

Camera& Camera::operator=(const Object& object) {
  Camera* other = (Camera*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  parent_ = other->GetParent();
  hsize_ = other->GetHorizontalSize();
  vsize_ = other->GetVerticalSize();
  field_of_view_ = other->GetFieldOfView();
  return *this;
}
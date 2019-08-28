#include <glm-0.9.5.3/glm/gtx/intersect.hpp>
#include "plane.hpp"

Plane::Plane() {
    point_ = {0,0,0};
    normal_ = {0,0,0};
}

Plane::Plane(glm::vec3 const &p1, glm::vec3 const &normal) {
    point_ = p1;
    normal_ = normal;
}

Plane::Plane(glm::vec3 const &p, glm::vec3 const &normal, std::string const &name,
             std::shared_ptr<Material> const mat_ptr) {
    point_ = p;
    normal_ = normal;
    name_ = name;
    material_ = mat_ptr;
}

Plane::~Plane() {}

float Plane::volume() const {
    return 0;
}

float Plane::area() const {
    return INFINITY;
}

std::ostream& Plane::print(std::ostream &os) const {
         os << "Name: " << name_ << " (Plane)" << std::endl;
         if (material_ != nullptr) {
             os << "Material: " << "[" << material_->name_ << "]" << std::endl;}
         else {
             os << "Material: " << "[" << "No Material" << "]" << std::endl
                << "Point : " << "[" << point_.x << ", " << point_.y << ", " << point_.z << "]" << std::endl
                << "Normal: " << "[" << normal_.x << ", " << normal_.y << ", " << normal_.z << "]" << std::endl;
         }
        return os;
}

Hitpoint Plane::intersect(Ray const &ray) const {
    Ray transformedRay = transformRay(ray, world_transformation_inv);
    float distance;
    bool hitted = glm::intersectRayPlane(transformedRay.origin_,glm::normalize(transformedRay.direction_),point_,glm::normalize(normal_),distance);
    if(hitted){
            glm::vec3 cutP = transformedRay.origin_ + distance * transformedRay.direction_;
            glm::vec4 trans_cutP =world_transformation_ * glm::vec4{cutP,1 };
            glm::vec4 trans_normal = glm::normalize(glm::transpose(world_transformation_inv) * glm::vec4{normal_,0 });
            Hitpoint hit;
            hit.hitpoint_ = {trans_cutP.x, trans_cutP.y, trans_cutP.z};
            hit.normal_ = {trans_normal.x, trans_normal.y, trans_normal.z};
            hit.direction_ = ray.direction_;
            hit.name_ = name_;
            hit.material_ = material_;
            hit.hit_ = true;
            hit.distance_ = glm::length(hit.hitpoint_-ray.origin_);
            return hit;
        }

    return Hitpoint{};
}
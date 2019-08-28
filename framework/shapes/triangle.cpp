#include "triangle.hpp"
#include <cmath>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "hitpoint.hpp"

Triangle::Triangle() {
    p1_ = {0, 0, 0};
    p2_ = {1, 1, 1};
    p3_ = {-1, -1, -1};
}

Triangle::Triangle(glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3) {
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
}

Triangle::Triangle(glm::vec3 const &p1, glm::vec3 const &p2, glm::vec3 const &p3, std::string const &name,
                   std::shared_ptr<Material> const mat_ptr) {
    p1_ = p1;
    p2_ = p2;
    p3_ = p3;
    material_ = mat_ptr;
    name_ = name;
}

Triangle::~Triangle() {}

//TODO volume of a plane?
float Triangle::volume() const {
    return 0;
}

float Triangle::area() const {
    return fabsf((p1_.x * (p2_.y - p3_.y) +
                  p2_.x * (p3_.y - p1_.y) +
                  p3_.x * (p1_.y - p2_.y)) / 2.0f);
}

std::ostream &Triangle::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Triangle)" << std::endl
                  << "Material: " << "[" << material_->name_ << "]" << std::endl
                  << "Point 1: " << "[" << p1_.x << ", " << p1_.y << ", " << p1_.z << "]" << std::endl
                  << "Point 2: " << "[" << p2_.x << ", " << p2_.y << ", " << p2_.z << "]" << std::endl
                  << "Point 3: " << "[" << p3_.x << ", " << p3_.y << ", " << p3_.z << "]" << std::endl;
    } else {
        return os << "Name: " << name_ << " (Triangle)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "Point 1: " << "[" << p1_.x << ", " << p1_.y << ", " << p1_.z << "]" << std::endl
                  << "Point 2: " << "[" << p2_.x << ", " << p2_.y << ", " << p2_.z << "]" << std::endl
                  << "Point 3: " << "[" << p3_.x << ", " << p3_.y << ", " << p3_.z << "]" << std::endl;
    }
}

// TODO implement intersect // not working
Hitpoint Triangle::intersect(Ray const &ray) const {
    glm::vec3 u, v, n;              // triangle vectors
    glm::vec3 w0, w;           // ray vectors
    float r, a, b;              // params to calc ray-plane intersect
    Ray transformedRay = transformRay(ray,world_transformation_inv);
    // get triangle edge vectors and plane normal
    u = p2_ - p1_;
    v = p3_ - p1_;
    n = glm::cross(u, v);
    if (n == glm::vec3{0, 0, 0})
        return Hitpoint{};           // triangle is a line or point

    w0 = transformedRay.origin_ - p1_;
    a = -glm::dot(n, w0);
    b = glm::dot(n, transformedRay.direction_);
    if (fabs(b) < 0.00000001) {     // ray is  parallel to triangle plane
        if (a == 0)                 // ray lies in triangle plane
            return Hitpoint{};
        else return Hitpoint{};     // ray disjoint from plane
    }

    r = a / b;
    if (r < 0.0)                    // ray goes away from triangle
        return Hitpoint{};         // no intersect
    glm::vec3 intersection_point = transformedRay.origin_ + r * transformedRay.direction_;
    float uu, uv, vv, wu, wv, D;
    uu = glm::dot(u, u);
    uv = glm::dot(u, v);
    vv = glm::dot(v, v);
    w = intersection_point - p1_;
    wu = glm::dot(w, u);
    wv = glm::dot(w, v);
    D = uv * uv - uu * vv;

    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // point is outside T
        return Hitpoint{};
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // point is outside T
        return Hitpoint{};
    Hitpoint hit = {true, r, name_, material_, ray.direction_, intersection_point,n};
    hit.name_ = name_;
    hit.hit_ = true;
    hit.material_ = material_;
    hit.direction_ = ray.direction_;
    glm::vec4 transformed_cut = world_transformation_ * glm::vec4{intersection_point,1 };
    glm::vec4 transformed_normal = glm::normalize(glm::transpose(world_transformation_inv) * glm::vec4{ n,0 });
    hit.hitpoint_ = {transformed_cut.x, transformed_cut.y, transformed_cut.z};
    hit.normal_ = {transformed_normal.x, transformed_normal.y, transformed_normal.z};
    hit.distance_ = glm::length(ray.origin_ - hit.hitpoint_);
    return hit;                       // I is in T
}



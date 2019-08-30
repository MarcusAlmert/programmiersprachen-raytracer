#include "box.hpp"
#include <cmath>
#include <vector>
#include <glm/vec3.hpp>
#include <algorithm>

Box::Box() {
    max_ = {0, 0, 0};
    min_ = {0, 0, 0};
}

Box::Box(glm::vec3 const &min, glm::vec3 const &max) {
    max_ = max;
    min_ = min;
    autocorrection(min_, max_);
}

Box::Box(glm::vec3 const &min, glm::vec3 const &max, std::string const &name,
         std::shared_ptr<Material> const &mat_ptr) :
        Shape{name, mat_ptr} {
    max_ = max;
    min_ = min;
    autocorrection(min_, max_);
}

Box::~Box() {
}

void autocorrection(glm::vec3 &min, glm::vec3 &max) {
    bool correct = true;
    if (min.x > max.x) {
        std::swap(min.x, max.x);
        correct = false;
    }
    if (min.y > max.y) {
        std::swap(min.y, max.y);
        correct = false;
    }
    if (min.z > max.z) {
        std::swap(min.z, max.z);
        correct = false;
    }
    if (!correct)
        std::cout << "\033[1;33m Box points were autocorrected! \033[0m\n";
}

float Box::area() const {
    return (2 * abs(max_.x - min_.x) * abs(max_.y - min_.y) +
            2 * abs(max_.x - min_.x) * abs(max_.z - min_.z) +
            2 * abs(max_.z - min_.z) * abs(max_.y - min_.y));
}

float Box::volume() const {
    return (abs(max_.x - min_.x) * abs(max_.y - min_.y) * abs(max_.z - min_.z));
}

std::ostream &Box::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Box)" << std::endl
                  << "Color: " << "[" << material_->name_ << "]" << std::endl
                  << "Min: " << "[" << min_.x << ", " << min_.y << ", " << min_.z << "]" << std::endl
                  << "Max: " << "[" << max_.x << ", " << max_.y << ", " << max_.z << "]" << std::endl
                  << "--------------------" << std::endl;
    } else {
        return os << "Name: " << name_ << " (Box)" << std::endl
                  << "Color: " << "[" << "No Material" << "]" << std::endl
                  << "Min: " << "[" << min_.x << ", " << min_.y << ", " << min_.z << "]" << std::endl
                  << "Max: " << "[" << max_.x << ", " << max_.y << ", " << max_.z << "]" << std::endl
                  << "--------------------" << std::endl;
    }
}

Hitpoint Box::intersect(Ray const &ray) const {
    Ray transformedRay = transformRay(ray, world_transformation_inv);
    Hitpoint hit{};
    bool hitted = false;
    float tmin = MAXFLOAT;

    //hinten
    float t = (min_.x - transformedRay.origin_.x) / (glm::normalize(transformedRay.direction_)).x;
    glm::vec3 p_x = transformedRay.origin_ + t * (glm::normalize(transformedRay.direction_));
    if (p_x.y <= max_.y && p_x.y >= min_.y
        && p_x.z <= max_.z && p_x.z >= min_.z && t > 0) {
        hitted = true;
        tmin = t;
        hit.hitpoint_ = p_x;
        hit.normal_ = glm::vec3{-1.0f, 0.0f, 0.0f};
    }

    //vorne
    float t_max_x = (max_.x - transformedRay.origin_.x) / (glm::normalize(transformedRay.direction_)).x;
    glm::vec3 p_x2 = transformedRay.origin_ + t_max_x * (glm::normalize(transformedRay.direction_));
    if (p_x2.y <= max_.y && p_x2.y >= min_.y
        && p_x2.z <= max_.z && p_x2.z >= min_.z && t_max_x > 0) {
        hitted = true;
        if (tmin > t_max_x) {
            hit.hitpoint_ = p_x2;
            tmin = t_max_x;
            hit.normal_ = glm::vec3{1.0f, 0.0f, 0.0f};
        }
    }

    //unten
    float t_min_y = (min_.y - transformedRay.origin_.y) / (glm::normalize(transformedRay.direction_)).y;
    glm::vec3 p_y = transformedRay.origin_ + t_min_y * (glm::normalize(transformedRay.
            direction_));
    if (p_y.x <= max_.x && p_y.x >= min_.x
        && p_y.z <= max_.z && p_y.z >= min_.z && t_min_y > 0) {
        hitted = true;
        if (tmin > t_min_y) {
            hit.hitpoint_ = p_y;
            tmin = t_min_y;
            hit.normal_ = glm::vec3{0.0f, -1.0f, 0.0f};
        }
    }

    //oben
    float t_max_y = (max_.y - transformedRay.origin_.y) / (glm::normalize(transformedRay.direction_)).y;
    glm::vec3 p_y2 = transformedRay.origin_ + t_max_y * (glm::normalize(transformedRay.direction_));
    if (p_y2.x <= max_.x && p_y2.x >= min_.x
        && p_y2.z <= max_.z && p_y2.z >= min_.z && t_max_y > 0) {
        hitted = true;
        if (tmin > t_max_y) {
            hit.hitpoint_ = p_y2;
            tmin = t_max_y;
            hit.normal_ = glm::vec3{0.0f, 1.0f, 0.0f};
        }
    }

    //rechts
    float t_min_z = (min_.z - transformedRay.origin_.z) / (glm::normalize(transformedRay.direction_)).z;
    glm::vec3 p_z = transformedRay.origin_ + t_min_z * (glm::normalize(transformedRay.direction_));
    if (p_z.y <= max_.y && p_z.y >= min_.y
        && p_z.x <= max_.x && p_z.x >= min_.x && t_min_z > 0) {
        hitted = true;
        if (tmin > t_min_z) {
            hit.hitpoint_ = p_z;
            tmin = t_min_z;
            hit.normal_ = glm::vec3{0.0f, 0.0f, -1.0f};
        }
    }

    //links
    float t_max_z = (max_.z - transformedRay.origin_.z) / (glm::normalize(transformedRay.direction_)).z;
    glm::vec3 p_z2 = transformedRay.origin_ + t_max_z * (glm::normalize(transformedRay.direction_));
    if (p_z2.y <= max_.y && p_z2.y >= min_.y
        && p_z2.x <= max_.x && p_z2.x >= min_.x && t_max_z > 0) {
        hitted = true;
        if (tmin > t_max_z) {
            hit.hitpoint_ = p_z2;
            tmin = t_max_z;
            hit.normal_ = glm::vec3{0.0f, 0.0f, 1.0f};

        }
    }

    if (hitted == true) {
        glm::vec4 transformed_point = world_transformation_ * glm::vec4{hit.hitpoint_, 1};
        glm::vec4 transformed_normal = glm::normalize(
                glm::transpose(world_transformation_inv) * glm::vec4{hit.normal_, 0});
        hit.hit_ = true;
        hit.material_ = material_;
        hit.direction_ = ray.direction_;
        hit.distance_ = tmin;
        hit.name_ = name_;
        hit.normal_ = glm::vec3{transformed_normal.x, transformed_normal.y, transformed_normal.z};
        hit.hitpoint_ = glm::vec3{transformed_point.x, transformed_point.y, transformed_point.z};
    }
    return hit;
}




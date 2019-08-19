#include "cone.hpp"

Cone::Cone() {
    pos_ = {0, 0, 0};
    height_ = 1;
    radius_ = 1;
}

Cone::Cone(glm::vec3 const &pos, float radius, float height) {
    pos_ = pos;
    height_ = height;
    radius_ = radius;
}

Cone::Cone(glm::vec3 const &pos, float radius, float height, std::string const &name,
           std::shared_ptr<Material> const mat_ptr) {
    pos_ = pos;
    height_ = height;
    radius_ = radius;
    name_ = name;
    material_ = mat_ptr;
}

Cone::~Cone() {}

float Cone::volume() const {
    return 1.0f / 3.0f * M_PI * pow(radius_, 2) * height_;
}

float Cone::area() const {
    return M_PI * pow(radius_, 2) + M_PI * radius_ * sqrt(pow(radius_, 2) + pow(height_, 2));
}

std::ostream &Cone::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name: " << name_ << " (Cone)" << std::endl
                  << "Material: " << "[" << material_->name_ << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    } else {
        return os << "Name: " << name_ << " (Cone)" << std::endl
                  << "Material: " << "[" << "No Material" << "]" << std::endl
                  << "Position: " << "[" << pos_.x << ", " << pos_.y << ", " << pos_.z << "]" << std::endl
                  << "Radius: " << radius_ << std::endl << "--------------------" << std::endl
                  << "Height " << height_ << std::endl;
    }
}

// TODO fix intersect
Hitpoint Cone::intersect(Ray const &ray) const {
    float a, b, c, t1, t2;
    glm::vec3 v = {pos_.x, pos_.y + height_, pos_.z};
    a = pow(ray.direction_.x, 2) + pow(ray.direction_.y, 2) - pow(ray.direction_.z, 2);
    b = 2 * ray.origin_.x * ray.direction_.x + 2 * ray.origin_.y * ray.direction_.y -
        2 * ray.origin_.z * ray.direction_.z;
    c = pow(ray.origin_.x, 2) + pow(ray.origin_.y, 2) - pow(ray.origin_.z, 2);
    t1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    t2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    if (b * b - 4 * a * c > 0) {
        bool c1 = false;
        bool c2 = false;
        glm::vec3 cutp1, cutp2;

        if (t1 > 0) {
            cutp1 = ray.origin_ + t1 * ray.direction_;
            if (cutp1.z <= 0.0f && cutp1.z >= -1.0f) {
                c1 = true;
            }
        }
        if (t2 > 0) {
            cutp2 = ray.origin_ + t2 * ray.direction_;
            if (cutp2.z <= 0.0f && cutp2.z >= -1.0f) {
                c2 = true;
            }
        }
        glm::vec3 cut_point, normal;
        float distance;
        bool cut = false;
        glm::vec3 proj_z;
        if (c1 && c2) {
            if (t2 < t1) {
                glm::vec3 cut_point = cutp2;
                float distance = t2;
                proj_z = glm::normalize(glm::vec3{cut_point.x, cut_point.y, 0});
                glm::vec3 normal = glm::normalize(glm::vec3{proj_z.x, proj_z.y, 1.0f});
                cut = true;
            } else {
                cut_point = cutp1;
                distance = t1;
                proj_z = glm::normalize(glm::vec3{cut_point.x, cut_point.y, 0});
                normal = glm::normalize(glm::vec3{proj_z.x, proj_z.y, 1.0f});
                cut = true;
            }
        } else if (c1) {
            cut_point = cutp1;
            distance = t1;
            proj_z = glm::normalize(glm::vec3{cut_point.x, cut_point.y, 0});
            normal = glm::normalize(glm::vec3{proj_z.x, proj_z.y, 1.0f});
            cut = true;
        } else if (c2) {
            cut_point = cutp2;
            distance = t2;
            proj_z = glm::normalize(glm::vec3{cut_point.x, cut_point.y, 0});
            normal = glm::normalize(glm::vec3{proj_z.x, proj_z.y, 1.0f});
            cut = true;
        }
        float distance_base = (glm::dot(glm::vec3{0, 0, -1}, {0, 0, -1}) - glm::dot(ray.origin_, {0, 0, -1})) /
                              (glm::dot(ray.direction_, {0, 0, -1}));
        glm::vec3 base_cut = ray.origin_ + distance_base * ray.direction_;
        if (distance_base > 0) {
            if (glm::length(base_cut - glm::vec3{0, 0, -1}) <= 1) {
                if ((c1 && c2 && distance_base < t1 && distance_base < t2) || (c1 && distance_base < t1) ||
                    (c2 && distance_base < t2)) {
                    cut_point = base_cut;
                    distance = distance_base;
                    normal = glm::normalize(glm::vec3{0, 0, -1.0f});
                    cut = true;
                }
            }
        }
        if (cut) {
            Hitpoint hitp{};
            hitp.hitpoint_ = cut_point;
            hitp.normal_ = normal;
            hitp.distance_ = distance = glm::length(cut_point - ray.origin_);
            hitp.direction_ = ray.direction_;
            hitp.name_ = name_;
            hitp.material_ = material_;
            hitp.hit_ = true;
            return hitp;
        }
    }
    return Hitpoint{};
}


        

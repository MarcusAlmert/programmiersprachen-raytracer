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
         std::shared_ptr<Material> const& mat_ptr) :
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
    Ray transRay = transformRay(ray,world_transformation_inv);
    Hitpoint hit;
    glm::vec3 normdirection = glm::normalize(transRay.direction_);

    std::vector<float> inBox;
    std::vector<glm::vec3> normals;

    // erst check ob direction parallel zur Ebene der Seite (dann ignoriert)
    // dann Berechnung des Schnittpunktes und Test ob Lage in Seiten der Box
    // t und die jeweilige normale werden in vectoren gespeichert
    // kleinste distanz am ende rausgesucht
    glm::vec3 hinten{-1, 0, 0};
    if (glm::dot(hinten, transRay.direction_) != 0) {
        auto t = glm::dot(normdirection, hinten);
        float t_hinten = (glm::dot(hinten, min_) - glm::dot(transRay.origin_, hinten)) / glm::dot(normdirection, hinten);
        glm::vec3 cutP = transRay.origin_ + normdirection * t_hinten;
        if (cutP.y > min_.y && cutP.y < max_.y && cutP.z > min_.z && cutP.z < max_.z) {
            inBox.push_back(t_hinten);
            normals.emplace_back(glm::vec3{-1, 0, 0});
        }
    }

    glm::vec3 rechts{0, 0, -1};
    if (glm::dot(rechts, transRay.direction_) != 0) {
        float t_rechts = (glm::dot(rechts, min_) - glm::dot(transRay.origin_, rechts)) / glm::dot(normdirection, rechts);
        glm::vec3 cutP = transRay.origin_ + normdirection * t_rechts;
        if (cutP.y > min_.y && cutP.y < max_.y && cutP.x > min_.x && cutP.x < max_.x) {
            inBox.push_back(t_rechts);
            normals.emplace_back(glm::vec3{0, 0, -1});
        }
    }

    glm::vec3 unten{0, -1, 0};
    if (glm::dot(unten, transRay.direction_) != 0) {
        float t_unten = (glm::dot(unten, min_) - glm::dot(transRay.origin_, unten)) / glm::dot(normdirection, unten);
        glm::vec3 cutP = transRay.origin_ + normdirection * t_unten;
        if (cutP.z > min_.z && cutP.z < max_.z && cutP.x > min_.x && cutP.x < max_.x) {
            inBox.push_back(t_unten);
            normals.emplace_back(glm::vec3{0, -1, 0});
        }
    }

    glm::vec3 vorne{1, 0, 0};
    if (glm::dot(vorne, transRay.direction_) != 0) {
        float t_vorne = (glm::dot(vorne, max_) - glm::dot(transRay.origin_, vorne)) / glm::dot(normdirection, vorne);
        glm::vec3 cutP = transRay.origin_ + normdirection * t_vorne;
        if (cutP.y > min_.y && cutP.y < max_.y && cutP.z > min_.z && cutP.z < max_.z) {
            inBox.push_back(t_vorne);
            normals.emplace_back(glm::vec3{1, 0, 0});
        }
    }

    glm::vec3 links{0, 0, 1};
    if (glm::dot(links, transRay.direction_) != 0) {
        float t_links = (glm::dot(links, max_) - glm::dot(transRay.origin_, links)) / glm::dot(normdirection, links);
        glm::vec3 cutP = transRay.origin_ + normdirection * t_links;
        if (cutP.y > min_.y && cutP.y < max_.y && cutP.x > min_.x && cutP.x < max_.x) {
            inBox.push_back(t_links);
            normals.emplace_back(glm::vec3{0, 0, 1});
        }

    }

    glm::vec3 oben{0, 1, 0};
    if (glm::dot(oben, transRay.direction_) != 0) {
        float t_oben = (glm::dot(oben, max_) - glm::dot(transRay.origin_, oben)) / glm::dot(normdirection, oben);
        glm::vec3 cutP = transRay.origin_ + normdirection * t_oben;
        if (cutP.z > min_.z && cutP.z < max_.z && cutP.x > min_.x && cutP.x < max_.x) {
            inBox.push_back(t_oben);
            normals.emplace_back(glm::vec3{0, 1, 0});
        }
    }
    if (inBox.empty()) {
        return Hitpoint{};
    } else {
        std::sort(inBox.begin(), inBox.end());
        float minimal = inBox[0];
        glm::vec3 minimal_normal = normals[0];
        for (unsigned long i = 1; i < inBox.size(); ++i){
            if (inBox[i] < minimal){
                minimal = inBox[i];
                minimal_normal = normals[i];
            }
        }

        float hitx = transRay.origin_.x + minimal * normdirection.x;
        float hity = transRay.origin_.y + minimal * normdirection.y;
        float hitz = transRay.origin_.z + minimal * normdirection.z;

        glm::vec4 trans_cut = world_transformation_ * glm::vec4({hitx,hity,hitz,1});
        glm::vec4 trans_normal = glm::normalize(glm::transpose(world_transformation_inv) * glm::vec4(minimal_normal,0));

        hit.material_ = material_;
        hit.name_ = name_;
        hit.hit_ = true;
        hit.hitpoint_ = {trans_cut.x,trans_cut.y,trans_cut.z};
        hit.normal_ = {trans_normal.x,trans_normal.y,trans_normal.z};
        hit.direction_ = ray.direction_;
        hit.distance_ = glm::length(hit.hitpoint_ - ray.origin_);
        return hit;
    }

}

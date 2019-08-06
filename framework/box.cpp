#include "box.hpp"
#include <cmath>
#include <vector>
#include <glm/vec3.hpp>
#include <algorithm>


Box::Box() {
    max = {0, 0, 0};
    min = {0, 0, 0};
}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_) {
    max = max_;
    min = min_;

}

Box::Box(glm::vec3 const &min_, glm::vec3 const &max_, std::string const &name_,
         std::shared_ptr<Material> const mat_ptr) :
        Shape{name_, mat_ptr} {
    max = max_;
    min = min_;;
}

Box::~Box() {
}

float Box::area() const {
    return (2 * abs(max.x - min.x) * abs(max.y - min.y) +
            2 * abs(max.x - min.x) * abs(max.z - min.z) +
            2 * abs(max.z - min.z) * abs(max.y - min.y));
}

float Box::volume() const {
    return (abs(max.x - min.x) * abs(max.y - min.y) * abs(max.z - min.z));
}

std::ostream &Box::print(std::ostream &os) const {
    if (material != nullptr) {
        return os << "Name: " << name << " (Box)" << std::endl
                  << "Color: " << "[" << material->name << "]" << std::endl
                  << "Min: " << "[" << min.x << ", " << min.y << ", " << min.z << "]" << std::endl
                  << "Max: " << "[" << max.x << ", " << max.y << ", " << max.z << "]" << std::endl
                  << "--------------------" << std::endl;
    } else {
        return os << "Name: " << name << " (Box)" << std::endl
                  << "Color: " << "[" << "No Material" << "]" << std::endl
                  << "Min: " << "[" << min.x << ", " << min.y << ", " << min.z << "]" << std::endl
                  << "Max: " << "[" << max.x << ", " << max.y << ", " << max.z << "]" << std::endl
                  << "--------------------" << std::endl;
    }
}

Hitpoint Box::intersect(Ray const &ray) const {
    Ray r = ray;
    Hitpoint hit;
    glm::vec3 normdirection = glm::normalize(ray.direction);

    //das war glaube was adrian meint ist egal
    std::vector<float> inBox;

    // erst check ob direction parallel zur Ebene der Seite (dann ignoriert)
    // dann Berechnung des Schnittpunktes und Test ob Lage in Seiten der Box
    // am Ende push in vector, dieser sortiert und kleinster Wert ist gesuchte Distanz
    glm::vec3 hinten{-1, 0, 0};
    if (glm::dot(hinten, ray.direction) != 0) {
        auto t = glm::dot(normdirection, hinten);
        float t_hinten = (glm::dot(hinten, min) - glm::dot(ray.origin, hinten)) / glm::dot(normdirection, hinten);
        glm::vec3 cutP = ray.origin + normdirection * t_hinten;
        if (cutP.y >= min.y && cutP.y <= max.y && cutP.z >= min.z && cutP.z <= max.z) {
            inBox.push_back(t_hinten);
        }
    }

    glm::vec3 rechts{0, 0, -1};
    if (glm::dot(rechts, ray.direction) != 0) {
        float t_rechts = (glm::dot(rechts, min) - glm::dot(ray.origin, rechts)) / glm::dot(normdirection, rechts);
        glm::vec3 cutP = ray.origin + normdirection * t_rechts;
        if (cutP.y >= min.y && cutP.y <= max.y && cutP.x >= min.x && cutP.x <= max.x) {
            inBox.push_back(t_rechts);
        }
    }

    glm::vec3 unten{0, -1, 0};
    if (glm::dot(unten, ray.direction) != 0) {
        float t_unten = (glm::dot(unten, min) - glm::dot(ray.origin, unten)) / glm::dot(normdirection, unten);
        glm::vec3 cutP = ray.origin + normdirection * t_unten;
        if (cutP.z >= min.z && cutP.z <= max.z && cutP.x >= min.x && cutP.x <= max.x) {
            inBox.push_back(t_unten);
        }
    }

    glm::vec3 vorne{1, 0, 0};
    if (glm::dot(vorne, ray.direction) != 0) {
        float t_vorne = (glm::dot(vorne, max) - glm::dot(ray.origin, vorne)) / glm::dot(normdirection, vorne);
        glm::vec3 cutP = ray.origin + normdirection * t_vorne;
        if (cutP.y >= min.y && cutP.y <= max.y && cutP.z >= min.z && cutP.z <= max.z) {
            inBox.push_back(t_vorne);
        }
    }

    glm::vec3 links{0, 0, 1};
    if (glm::dot(links, ray.direction) != 0) {
        float t_links = (glm::dot(links, max) - glm::dot(ray.origin, links)) / glm::dot(normdirection, links);
        glm::vec3 cutP = ray.origin + normdirection * t_links;
        if (cutP.y >= min.y && cutP.y <= max.y && cutP.x >= min.x && cutP.x <= max.x) {
            inBox.push_back(t_links);
        }

    }

    glm::vec3 oben{0, 1, 0};
    if (glm::dot(oben, ray.direction) != 0) {
        float t_oben = (glm::dot(oben, max) - glm::dot(ray.origin, oben)) / glm::dot(normdirection, oben);
        glm::vec3 cutP = ray.origin + normdirection * t_oben;
        if (cutP.z >= min.z && cutP.z <= max.z && cutP.x >= min.x && cutP.x <= max.x) {
            inBox.push_back(t_oben);
        }
    }
    if (inBox.empty()) {
        return Hitpoint{};
    } else {
        std::sort(inBox.begin(), inBox.end());
        float minimal = inBox[0];
        hit.material = material;
        hit.name = name;
        hit.distance = minimal;
        hit.hit = true;
        hit.direction = r.direction;
        float hitx = ray.origin.x + minimal * normdirection.x;
        float hity = ray.origin.y + minimal * normdirection.y;
        float hitz = ray.origin.z + minimal * normdirection.z;
        hit.hitpoint = {hitx, hity, hitz};
        return hit;
    }

}

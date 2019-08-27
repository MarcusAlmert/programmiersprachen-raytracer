#include "ray.hpp"

Ray transformRay(const Ray &ray, const glm::mat4 &mat) {
        //create homogen coordinates
        glm::vec4 origin{ray.origin_,1};
        glm::vec4 direction{ray.direction_,0};
        origin = mat*origin;
        direction = mat*direction;
        return Ray{glm::vec3{origin.x,origin.y,origin.z},glm::vec3{direction.x,direction.y,direction.z}};
}

#include "cylinder.hpp"

Cylinder::Cylinder() :
    pos1_{glm::vec3{0, 0, 0}}, pos2_{glm::vec3{0, 0, 0}}, radius_{0.0f} {
        name_ = "EmptyCylinder";
        material_ = nullptr;
    }

Cylinder::Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius) :
    pos1_{pos1}, pos2_{pos2}, radius_{radius}
    {
        name_ = "UnnamedCylinder";
        material_ = nullptr;
    }

Cylinder::Cylinder(glm::vec3 const &pos1, glm::vec3 const& pos2, float radius, std::string const &name,
                   std::shared_ptr<Material> const &mat_ptr) :
    pos1_{pos1}, pos2_{pos2}, radius_{radius} {
        name_ = name;
        material_ = mat_ptr;
    }

Cylinder::~Cylinder() {}

float Cylinder::area() const {
    return 2 * M_PI * powf(radius_, 2.0f) + 2 * M_PI * radius_ * glm::distance(pos1_, pos2_);
}

float Cylinder::volume() const {
    return M_PI * powf(radius_, 2.0f) * glm::distance(pos1_, pos2_);
}

float Cylinder::get_height() const{
    return glm::distance(pos1_, pos2_);
}

std::ostream &Cylinder::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name:       " << name_ << " (Cylinder)" << std::endl
                  << "Material:   " << "[" << material_->name_ << "]" << std::endl
                  << "CapCenter1: " << "[" << pos1_.x << ", " << pos1_.y << ", " << pos1_.z << "]" << std::endl
                  << "CapCenter2: " << "[" << pos2_.x << ", " << pos2_.y << ", " << pos2_.z << "]" << std::endl
                  << "Radius:     " << radius_ << std::endl
                  << "Height:     " << get_height() << std::endl
                  << "--------------------" << std::endl;
    } else {
        return os << "Name:       " << name_ << " (Cylinder)" << std::endl
                  << "Material:   " << "[" << "No Material" << "]" << std::endl
                  << "CapCenter1: " << "[" << pos1_.x << ", " << pos1_.y << ", " << pos1_.z << "]" << std::endl
                  << "CapCenter2: " << "[" << pos2_.x << ", " << pos2_.y << ", " << pos2_.z << "]" << std::endl
                  << "Radius:     " << radius_ << std::endl
                  << "Height:     " << get_height() << std::endl
                  << "--------------------" << std::endl;
    }
}

Hitpoint Cylinder::intersect(Ray const &ray) const {
    Ray transformedRay = transformRay(ray, world_transformation_inv);
    glm::vec3 cylinder_direction = glm::normalize(pos2_ - pos1_);
    glm::vec3 ray_direction = glm::normalize(transformedRay.direction_);
    glm::vec3 delta_p = transformedRay.origin_ - pos1_;
    float A = powf(glm::length((ray_direction - glm::dot(ray_direction, cylinder_direction) * cylinder_direction)), 2.0f);
    float B = 2 * glm::dot((ray_direction - glm::dot(ray_direction, cylinder_direction) * cylinder_direction), 
                            delta_p - glm::dot(delta_p, cylinder_direction) * cylinder_direction);
    float C = powf(glm::length(delta_p - glm::dot(delta_p, cylinder_direction) * cylinder_direction), 2.0f) - powf(radius_, 2.0f);

    // solving the square equation with a-b-c-formula
    float t1 = -1.0f;
    float t2 = -1.0f;
    float inside_sqrt = sqrtf(std::max(0.0f, powf(B, 2.0f) - 4 * A * C));
    float doubled_a = 2 * A;
    if (inside_sqrt > 0.00001f){
        t1 = (-1.0f * B + inside_sqrt) / doubled_a;
        t2 = (-1.0f * B - inside_sqrt) / doubled_a;
    }
    

    // container for hit candidates (min = 0, max = 4);
    std::vector<Hitpoint> candidates;

    // first check for two possible hits on the body of the cylinder
    if (t1 > 0.00001f){
        Hitpoint hitpoint{};
        glm::vec3 hit_point = transformedRay.origin_ + ray_direction * t1;
        glm::vec4 trans_cut = world_transformation_ * glm::vec4(hit_point,1);
        hitpoint.hitpoint_ = glm::vec3{trans_cut.x,trans_cut.y,trans_cut.z};
        hitpoint.distance_ = glm::length(ray.origin_- hitpoint.hitpoint_);
        if (glm::dot(cylinder_direction, hit_point - pos1_) > 0 && glm::dot(cylinder_direction, hit_point - pos2_) < 0){
        hitpoint.hit_ = true;
        hitpoint.normal_ = calc_normal_corpus(hit_point);
        candidates.emplace_back(hitpoint);
        }
    }
    if (t2 > 0.00001f){
        Hitpoint hitpoint{};
        glm::vec3 hit_point = transformedRay.origin_ + ray_direction * t2;
        glm::vec4 trans_cut = world_transformation_ * glm::vec4(hit_point,1);
        hitpoint.hitpoint_ = glm::vec3{trans_cut.x,trans_cut.y,trans_cut.z};
        hitpoint.hit_ = true;
        hitpoint.distance_ = glm::length(ray.origin_-hitpoint.hitpoint_);
        if (glm::dot(cylinder_direction, hit_point - pos1_) > 0 && glm::dot(cylinder_direction, hit_point - pos2_) < 0){
        hitpoint.normal_ = calc_normal_corpus(hit_point);
        candidates.emplace_back(hitpoint);
        }
    }
    
    // calculating distance between origin of ray and fields of the caps
    float t3 = (glm::dot(cylinder_direction, pos1_) - glm::dot(cylinder_direction, transformedRay.origin_)) / glm::dot(ray_direction, cylinder_direction);
    float t4 = (glm::dot(cylinder_direction, pos2_) - glm::dot(cylinder_direction, transformedRay.origin_)) / glm::dot(ray_direction, cylinder_direction);

    // t3 and t4 are candidates if hit is on the cap of the cylinder
    if (t3 > 0.0001f){
        glm::vec3 hit_point = transformedRay.origin_ + ray_direction * t3;


        float q3_minus_p1_length_squared = powf(glm::length(hit_point - pos1_),2.0f);
        if (q3_minus_p1_length_squared < powf(radius_, 2.0f)){

            Hitpoint hitpoint{};
            glm::vec4 trans_cut = world_transformation_ * glm::vec4(hit_point, 1.0f);
            glm::vec4 trans_normal = glm::normalize(glm::transpose(world_transformation_inv) * glm::vec4(glm::normalize(pos1_ - pos2_),0));
            hitpoint.hitpoint_ = {trans_cut.x,trans_cut.y,trans_cut.z};
            hitpoint.normal_ = {trans_normal.x,trans_normal.y,trans_normal.z};
            hitpoint.hit_ = true;
            hitpoint.distance_ = glm::length(ray.origin_-hitpoint.hitpoint_);
            candidates.emplace_back(hitpoint);
        }
    }
    if (t4 > 0.0001f){
        glm::vec3 hit_point = transformedRay.origin_ + ray_direction * t4;
        float q4_minus_p2_length_squared = powf(glm::length(hit_point - pos2_), 2.0f);
        if (q4_minus_p2_length_squared < powf(radius_, 2.0f)){

            glm::vec4 trans_cut = world_transformation_ * glm::vec4(hit_point,1);
            glm::vec4 trans_normal = glm::normalize(
                    glm::transpose(world_transformation_inv) * glm::vec4(glm::normalize(cylinder_direction), 0));
            Hitpoint hitpoint{};
            hitpoint.hitpoint_ = {trans_cut.x,trans_cut.y,trans_cut.z};
            hitpoint.normal_ = {trans_normal.x,trans_normal.y,trans_normal.z};
            hitpoint.hit_ = true;
            hitpoint.distance_ = glm::length(ray.origin_-hitpoint.hitpoint_);
            candidates.emplace_back(hitpoint);
        }
    }

    Hitpoint final_hitpoint{};

    // the final hitpoint is the one with the minimal t
    for (unsigned int i = 0; i < candidates.size(); i++){
        if (candidates[i].distance_ < final_hitpoint.distance_){
            final_hitpoint = candidates[i];
        }
    }

    // in case of hit setting the member variables that are left and are same for every hitpoint
    if (final_hitpoint.hit_){
        final_hitpoint.name_ = name_;
        final_hitpoint.material_ = material_;
        final_hitpoint.direction_ = ray.direction_;
    }

    return final_hitpoint;
}

glm::vec3 Cylinder::calc_normal_corpus(glm::vec3 const& hitpoint) const{
    glm::vec3 cylinder_direction = pos2_ - pos1_;
    float r = (glm::dot(cylinder_direction, hitpoint) - glm::dot(cylinder_direction, pos1_)) / glm::dot(cylinder_direction,cylinder_direction);
    glm::vec3 normal{hitpoint.x -(pos1_.x + r * cylinder_direction.x),
                     hitpoint.y -(pos1_.y + r * cylinder_direction.y),
                     hitpoint.z -(pos1_.z + r * cylinder_direction.z)};

    glm::vec4 trans_normal = glm::normalize(
            glm::transpose(world_transformation_inv) * glm::vec4(glm::normalize(normal), 0));

    return {trans_normal.x,trans_normal.y,trans_normal.z};
}
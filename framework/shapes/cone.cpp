#include "cone.hpp"

Cone::Cone() :
    base_center_pos_{glm::vec3{0.0f, 0.0f, 0.0f}}, tip_pos_{glm::vec3{0.0f, 0.0f, 0.0f}}, radius_{0}
    {}

Cone::Cone(glm::vec3 const &base_pos, glm::vec3 const& tip_pos, float radius) :
    base_center_pos_{base_pos}, tip_pos_{tip_pos}, radius_{radius}
    {}

Cone::Cone(glm::vec3 const &base_pos, glm::vec3 const& tip_pos, float radius, std::string const &name,
           std::shared_ptr<Material> const mat_ptr) :
           base_center_pos_{base_pos}, tip_pos_{tip_pos}, radius_{radius}
           {
               name_ = name;
               material_ = mat_ptr;
           }

Cone::~Cone() {}

float Cone::volume() const {
    return (1.0f / 3.0f) * M_PI * powf(radius_, 2.0f) * glm::length(base_center_pos_ - tip_pos_);
}

float Cone::area() const {
    return M_PI * powf(radius_, 2.0f) + M_PI * radius_ * sqrtf(powf(radius_, 2.0f) + powf(glm::length(base_center_pos_ - tip_pos_), 2.0f));
}

std::ostream &Cone::print(std::ostream &os) const {
    if (material_ != nullptr) {
        return os << "Name:         " << name_ << " (Cone)" << std::endl
                  << "Material:     " << "[" << material_->name_ << "]" << std::endl
                  << "Base Center:  " << "[" << base_center_pos_.x << ", " << base_center_pos_.y << ", " << base_center_pos_.z << "]" << std::endl
                  << "Tip Position: " << "[" << tip_pos_.x << ", " << tip_pos_.y << ", " << tip_pos_.z << "]" << std::endl
                  << "Radius:       " << radius_ << std::endl << "--------------------" << std::endl;
    } else {
        return os << "Name:         " << name_ << " (Cone)" << std::endl
                  << "Material:     " << "[" << "No Material" << "]" << std::endl
                  << "Base Center:  " << "[" << base_center_pos_.x << ", " << base_center_pos_.y << ", " << base_center_pos_.z << "]" << std::endl
                  << "Tip Position: " << "[" << tip_pos_.x << ", " << tip_pos_.y << ", " << tip_pos_.z << "]" << std::endl
                  << "Radius:       " << radius_ << std::endl << "--------------------" << std::endl;
    }
}

// TODO fix intersect
Hitpoint Cone::intersect(Ray const &ray) const {

    Ray transformedRay = transformRay(ray, world_transformation_inv);
    glm::vec3 cone_direction = glm::normalize(tip_pos_ - base_center_pos_);
    glm::vec3 reverse_cone_direction = -1.0f * cone_direction;
    glm::vec3 ray_direction = glm::normalize(transformedRay.direction_);
    //float a, b, c;
    glm::vec3 v{tip_pos_};
    glm::vec3 delta_p = transformedRay.origin_ - tip_pos_;
    glm::vec3 radius_direction;
    if (cone_direction.x == 0.0f && cone_direction.z == 0.0f){
        radius_direction = glm::vec3{1.0f, 0.0f, 0.0f};
    } else {
        radius_direction = glm::normalize(glm::vec3{cone_direction.z, 0.0f, -1.0f * cone_direction.x});
    }
    //glm::vec3 radius_direction = glm::normalize(glm::vec3{cone_direction.z, 0.0f, -1.0f * cone_direction.x});
    glm::vec3 edge_point = base_center_pos_ + radius_ * radius_direction;
    glm::vec3 direction_to_egde = edge_point - tip_pos_;
    float cos_alpha = glm::dot(direction_to_egde, reverse_cone_direction) / glm::length(direction_to_egde) * glm::length(reverse_cone_direction); 
    float cos_apha_squared = powf(cos_alpha, 2.0f);
    float sin_aplha_squared = powf(sinf(acosf(cos_alpha)), 2.0f);

    //glm::vec3 v = {pos_.x, pos_.y + height_, pos_.z};
    /*
    a = pow(ray.direction_.x, 2) + pow(ray.direction_.y, 2) - pow(ray.direction_.z, 2);
    b = 2 * ray.origin_.x * ray.direction_.x + 2 * ray.origin_.y * ray.direction_.y -
        2 * ray.origin_.z * ray.direction_.z;
    c = pow(ray.origin_.x, 2) + pow(ray.origin_.y, 2) - pow(ray.origin_.z, 2); */

    float dot_v_va = glm::dot(ray_direction, cone_direction);
    float dot_dp_va = glm::dot(delta_p, cone_direction);
    float A = cos_apha_squared * powf(glm::length(ray_direction - dot_v_va *cone_direction), 2.0f) -
              sin_aplha_squared * powf(dot_v_va, 2.0f);
    float B = 2.0f * cos_apha_squared * glm::dot(ray_direction - dot_v_va * cone_direction, delta_p - dot_dp_va * cone_direction) - 
              2.0f * sin_aplha_squared * dot_v_va * dot_dp_va;
    float C = cos_apha_squared * powf(glm::length((delta_p - dot_dp_va * cone_direction)), 2.0f) -
              sin_aplha_squared * powf(glm::length(dot_dp_va), 2.0f);

    //t1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    //t2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

    // solving the square equation with a-b-c-formula
    float t1 = -1.0f;
    float t2 = -1.0f;
    float inside_sqrt = sqrtf(std::max(0.0f, powf(B, 2.0f) - 4 * A * C));
    float doubled_a = 2 * A;
    if (inside_sqrt > 0.00001f){
        t1 = (-1.0f * B + inside_sqrt) / doubled_a;
        t2 = (-1.0f * B - inside_sqrt) / doubled_a;
    }

    // container for hit candidates (min = 0, max = 3);
    std::vector<Hitpoint> candidates;

    if (t1 > 0.00001){
        Hitpoint hitpoint{};
        glm::vec3 hit_point = transformedRay.origin_ + ray_direction * t1;
        glm::vec4 trans_cut = world_transformation_ * glm::vec4(hit_point, 1);
        hitpoint.hitpoint_ = glm::vec3{trans_cut.x, trans_cut.y, trans_cut.z};
        hitpoint.distance_ = glm::length(ray.origin_ - hitpoint.hitpoint_);
        if (glm::dot(cone_direction, hit_point - base_center_pos_) > 0 && 
            glm::dot(cone_direction, hit_point - tip_pos_) < 0){
                hitpoint.hit_ = true;
                hitpoint.normal_ = calc_normal_corpus(hit_point);
                candidates.emplace_back(hitpoint);
            }
    }
    if (t2 > 0.00001){
        Hitpoint hitpoint{};
        glm::vec3 hit_point = transformedRay.origin_ + cone_direction * t2;
        glm::vec4 trans_cut = world_transformation_ * glm::vec4(hit_point, 1);
        hitpoint.hitpoint_ = glm::vec3{trans_cut.x, trans_cut.y, trans_cut.z};
        hitpoint.hit_ = true;
        hitpoint.distance_ = glm::length(ray.origin_ - hitpoint.hitpoint_);
        if (glm::dot(cone_direction, hit_point - base_center_pos_) > 0 && 
            glm::dot(cone_direction, hit_point - tip_pos_) < 0){
                hitpoint.hit_ = true;
                hitpoint.normal_ = calc_normal_corpus(hit_point);
                candidates.emplace_back(hitpoint);
            }
    }

    float t3 = (glm::dot(cone_direction, base_center_pos_) - glm::dot(cone_direction, transformedRay.origin_)) / glm::dot(cone_direction, ray_direction);

    if (t3 > 0.00001){
        glm::vec3 hit_point = transformedRay.origin_ + ray_direction * t3;
        float q3_minus_base_center_length_squared = powf(glm::length(hit_point - base_center_pos_), 2.0f);
        if (q3_minus_base_center_length_squared < powf(radius_, 2.0f)){

            Hitpoint hitpoint{};
            glm::vec4 trans_cut = world_transformation_ * glm::vec4(hit_point, 1.0f);
            glm::vec4 trans_normal = glm::normalize(glm::transpose(world_transformation_inv) * glm::vec4(glm::normalize(base_center_pos_ - tip_pos_),0));
            hitpoint.hitpoint_ = glm::vec3{trans_cut.x, trans_cut.y, trans_cut.z};
            hitpoint.normal_ = glm::vec3{trans_normal.x, trans_normal.y, trans_normal.z};
            hitpoint.hit_ = true;
            hitpoint.distance_ = t3;
            candidates.emplace_back(hitpoint);
        }
    }
    /*
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
    */

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

float Cone::get_height() const{
    return (glm::length(base_center_pos_ - tip_pos_));
}

glm::vec3 Cone::calc_normal_corpus(glm::vec3 const& hitpoint) const{

    float h1 = hitpoint.x - base_center_pos_.x;
    float h2 = hitpoint.z - base_center_pos_.z;
    float r = sqrtf(powf(h1, 2.0f) + powf(h2, 2.0f));
    glm::vec3 normal{h1, r * (radius_ / glm::length(tip_pos_ - base_center_pos_)), h2};
    return glm::normalize(normal);
}
        

// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const &file)
        : width_(w), height_(h), color_buffer_(w * h, Color(0.0, 0.0, 0.0)), filename_(file), ppm_(width_, height_) {}

void Renderer::render(Scene const &scene) {
    //std::size_t const checker_pattern_size = 20;

    float d = (width_ / 2) / tan(scene.cam.fov / 2 * M_PI / 180);

    glm::vec3 dir = glm::normalize(scene.cam.direction);    // vector in direction of view
    glm::vec3 up = glm::normalize(scene.cam.upVector);  // vector in above direction from origin
    glm::vec3 l = glm::normalize(glm::cross(up, dir));  // vector in left direction from origin
    glm::vec3 r = glm::normalize(glm::cross(dir, up));  // vector in right direction from origin



    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            Pixel p(x, y);

            glm::vec3 pos = scene.cam.position;
            glm::vec3 direction = glm::normalize(scene.cam.direction);

            direction = direction + glm::vec3{x - (0.5f * width_), y - (0.5f * height_), pos.z - d};

            // in dieser Schleife wird der Schnittpunkt mit dem ersten Objekt den der Strahl trifft berechnet
            Hitpoint first_hit = fire_ray(scene, Ray{pos, glm::normalize(direction)});

            // Entweder es wurde ein Objekt getroffen oder der Pixel bekommt die Hintergrundfarbe zugewiesen
            if (first_hit.hit) {
                Color raytracer_color = calc_color(first_hit, scene, 3);
                tone_mapping(raytracer_color);
                p.color = raytracer_color;
                //p.color = Color{1.0f, 0.0f, 0.0f};
            } else {
                p.color = Color{0.0f, 0.0f, 0.0f};
            }

            /*
            if (((x / checker_pattern_size) % 2) != ((y / checker_pattern_size) % 2)) {
                p.color = Color(0.0, 1.0, float(x) / height_);
            } else {
                p.color = Color(1.0, 0.0, float(y) / width_);
            }
            */
            write(p);
        }
    }
    ppm_.save(filename_);
}

void Renderer::write(Pixel const &p) {
    // flip pixels, because of opengl glDrawPixels
    size_t buf_pos = (width_ * p.y + p.x);
    if (buf_pos >= color_buffer_.size() || (int) buf_pos < 0) {
        std::cerr << "Fatal Error Renderer::write(Pixel p) : "
                  << "pixel out of ppm_ : "
                  << (int) p.x << "," << (int) p.y
                  << std::endl;
    } else {
        color_buffer_[buf_pos] = p.color;
    }

    ppm_.write(p);
}

// Farbwertberechnung, TODO ! Weiter Funktionen für Reflexionen etc. notwendig
Color Renderer::calc_color(Hitpoint hitpoint, Scene const &scene, unsigned int reflaction_steps) {
    Color raytracer_value = Color(0.0f, 0.0f, 0.0f);
    Color ambient = calc_ambient(hitpoint.material, scene);
    Color diffuse = calc_diffuse(hitpoint, scene);
    Color specular = calc_specular(hitpoint, scene);
    return (raytracer_value + ambient + diffuse + specular);
}

//TODO calc_phong
//TODO calc_reflection
//TODO calc_refraction

// Diese Funktion ist in soweit fertig holt nur ka aus dem Material
Color Renderer::calc_ambient(std::shared_ptr<Material> material, Scene const &scene) {
    Color ambient = Color{scene.ambient, scene.ambient, scene.ambient};
    return (ambient *= material->ka);
}

// TODO fix graphical bug // maybe fixed
Color Renderer::calc_diffuse(Hitpoint hitpoint, Scene const &scene) {
    Color final{0, 0, 0};
    std::vector<Color> lights_color;
    for (auto light: scene.lights) {
        bool light_not_visible = false;
        glm::vec3 cut_point;
        glm::vec3 new_normal;
        glm::vec3 vec_light_cut = glm::normalize(light.position_ - hitpoint.hitpoint);

        //überprüfen ob zwischen objekt und Punktlichtquelle andere Objekte liegen
        for (auto shape : scene.shape_vector) {
            light_not_visible = shape->intersect(Ray{hitpoint.hitpoint + 0.1f * hitpoint.normal, vec_light_cut}).hit;
            if (light_not_visible) {
                light_not_visible = true;
                break;  // if there is atleast one shape in between light and current shape light gets blocked
            }
        }
        // if there is no light blocking shape
        if (light_not_visible == false) {
            float o = glm::dot(vec_light_cut, glm::normalize(hitpoint.normal));
            Color i_p = light.color_ * light.brightness_;
            Color k_d = hitpoint.material->kd;
            lights_color.push_back(k_d * i_p * o);
        }
    }
    for (auto color: lights_color) {
        final += color;
    }
    return final;
}

Color Renderer::calc_specular(Hitpoint hitpoint, Scene const &scene) {
    Color final{0, 0, 0};
    std::vector<Color> lights_color;
    for (auto light: scene.lights) {
        bool light_not_visible = false;
        glm::vec3 cut_point;
        glm::vec3 new_normal;
        glm::vec3 vec_light_cut = glm::normalize(light.position_ - hitpoint.hitpoint);

        //überprüfen ob zwischen objekt und Punktlichtquelle andere Objekte liegen
        for (auto shape : scene.shape_vector) {
            light_not_visible = shape->intersect(Ray{hitpoint.hitpoint + 0.2f * hitpoint.normal, vec_light_cut}).hit;
            if (light_not_visible) {
                light_not_visible = true;
                break;  // if there is atleast one shape in between light and current shape light gets blocked
            }
        }
        // if there is no light blocking shape
        if (light_not_visible == false) {
            glm::vec3 camera_hitpoint = glm::normalize(scene.cam.position - hitpoint.hitpoint);
            glm::vec3 r = glm::dot(hitpoint.normal, vec_light_cut) * 2.0f * hitpoint.normal - vec_light_cut;
            float p = abs(glm::dot(r, camera_hitpoint));
            float cos = pow(p, hitpoint.material->m);
            float m_pi = (hitpoint.material->m + 2) / (2 * M_PI);
            Color i_p = light.color_ * light.brightness_;
            Color k_s = hitpoint.material->ks;
            lights_color.push_back(k_s * m_pi * cos * i_p);
        }
    }
    for (auto color: lights_color) {
        final += color;
    }
    return final;
}

// Berechnung der Spiegelung noch nicht ganz ausgereift.
Color Renderer::calc_reflection(Hitpoint const& hitpoint, Scene const& scene, unsigned int recursive_boundary){
    Color final{0, 0, 0};
    glm::vec3 incoming_direction = glm::normalize(hitpoint.direction);
    glm::vec3 normal = glm::normalize(hitpoint.normal);
    glm::vec3 reflaction_ray_direction = incoming_direction - 2 * (glm::dot(normal, incoming_direction)) * normal;
    Ray reflaction_ray{hitpoint.hitpoint, glm::normalize(reflaction_ray_direction)};
    Hitpoint next_hit = fire_ray(scene, reflaction_ray);

    if (hitpoint.hit == false){
        return Color{0, 0, 0};
    } else {
        if (recursive_boundary > 0){
            Color reflected_color = calc_color(next_hit, scene, recursive_boundary - 1) * 0.8;
            return reflected_color;
        } else {
            return Color{0, 0, 0};
        }
    }
}

Hitpoint Renderer::fire_ray(Scene const& scene, Ray const& ray){
    Hitpoint first_hit;
    first_hit.distance = FLT_MAX;
    for (int i = 0; i < scene.shape_vector.size(); ++i) {
        Hitpoint hit = scene.shape_vector[i]->intersect(ray);
        if (hit.hit && hit.distance < first_hit.distance) {
            first_hit = hit;
        }
    }
    return first_hit;
}

// Diese Funktion macht am Ende das tone mapping
void Renderer::tone_mapping(Color &color) {
    color.r = color.r / (color.r + 1);
    color.g = color.g / (color.g + 1);
    color.b = color.b / (color.b + 1);
}
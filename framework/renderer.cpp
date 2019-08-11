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

void Renderer::render(Scene const& scene) {
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

            direction = direction + glm::vec3{x - (0.5f * width_), y - (0.5f * height_), -d};

            Hitpoint first_hit;
            first_hit.distance = FLT_MAX;

            // in dieser Schleife wird der Schnittpunkt mit dem ersten Objekt den der Strahl trifft berechnet
            for (int i = 0; i < scene.shape_vector.size(); ++i){
                Hitpoint hit = scene.shape_vector[i]->intersect(Ray{pos, glm::normalize(direction)});
                if (hit.hit && hit.distance < first_hit.distance){
                    first_hit = hit;
                }
            }

            // Entweder es wurde ein Objekt getroffen oder der Pixel bekommt die Hintergrundfarbe zugewiesen
            if (first_hit.hit){
                Color raytracer_color = calc_color(first_hit.material, scene);
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
Color Renderer::calc_color(std::shared_ptr<Material> material, Scene const& scene){
    Color raytracer_value = Color(0.0f, 0.0f, 0.0f);
    return (raytracer_value + material->kd + calc_ambient(material, scene));
}


// Diese Funktion ist in soweit fertig holt nur ka aus dem Material
Color Renderer::calc_ambient(std::shared_ptr<Material> material, Scene const& scene){
    Color ambient = Color{scene.ambient, scene.ambient, scene.ambient};
    return (ambient*=material->ka);
}

Color Renderer::calc_diffuse(std::shared_ptr<Material> material, Scene const &scene) {
    Color final{0, 0, 0};
    std::vector<Color> lights_color;
    for (auto light: scene.lights) {
        bool light_visible = true;
        glm::vec3 cut;
        glm::vec3 normale;
        glm::vec3 light_cut = glm::normalize(light.position_ - cut);

        //TODO überprüfen ob zwischen objekt und Punktlichtquelle andere Objekte liegen
        // (verdecken licht)
        // und beide fälle berechnen (kommt noch)
    }
}

// Diese Funktion macht am Ende das tone mapping
void Renderer::tone_mapping(Color & color){
    color.r = color.r / (color.r + 1);
    color.g = color.g / (color.g + 1);
    color.b = color.b / (color.b + 1);
}
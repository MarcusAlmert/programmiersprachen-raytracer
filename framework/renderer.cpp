#include <glm-0.9.5.3/glm/gtx/transform.hpp>
#include "renderer.hpp"
#include <thread>
#include <chrono>

Renderer::Renderer(unsigned w, unsigned h, std::string const &file)
        : width_(w), height_(h), color_buffer_(w * h, Color(0.0, 0.0, 0.0)), filename_(file), ppm_(width_, height_) {}

void Renderer::render(Scene const &scene) {
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "==================================" << std::endl;
    std::cout << "                                              " << std::endl;
    Scene rotate_scene = scene;
    float angle = 360 / rotate_scene.frames;
    long elapsed_time;

    for (int i = 0; i < rotate_scene.frames; i++) {
        glm::vec3 distance{0.0f, 0.0f, 0.0f};   // additional distance for camera rotation
        glm::mat4x4 rotation = glm::rotate((float) angle * i, glm::vec3{0.0f, 1.0f, 0.0f});
        glm::vec4 n_4 = glm::vec4{rotate_scene.camera_.direction, 0} * rotation;
        glm::vec4 up_4 = glm::vec4{rotate_scene.camera_.upVector, 0} * rotation;
        glm::vec3 dir = glm::normalize(glm::vec3{n_4.x, n_4.y, n_4.z});
        glm::vec3 up = glm::vec3{up_4.x, up_4.y, up_4.z};
        glm::vec3 u = glm::normalize(glm::cross(dir, up));
        glm::vec3 v = glm::normalize(glm::cross(u, dir));
        float x = (glm::vec4{distance, 1.0f} * rotation).x;
        float z = (glm::vec4{distance, 1.0f} * rotation).z;
        rotate_scene.camera_.transformation_ = glm::mat4{
                glm::vec4{u, 0.0f},
                glm::vec4{v, 0.0f},
                glm::vec4{-dir, 0.0f},
                glm::vec4{x, 50.0f, z, 1.0f}
        };

        std::string picture_name = rotate_scene.filename + std::to_string(i) + ".ppm";
        float d = (width_ / 2) / tan(rotate_scene.camera_.fov / 2 * M_PI / 180);

        glm::vec3 down = up;
        invert_direction(down);                // vector in down direction from origin
        glm::vec3 l = glm::normalize(glm::cross(up, dir));          // vector in left direction from origin
        glm::vec3 r = glm::normalize(glm::cross(dir, up));          // vector in right direction from origin

        float half_height = height_ / 2.0f;
        float half_width = width_ / 2.0f;
        glm::vec3 zr = d * dir;                                     // distance of pixel from "eye" position
        glm::vec3 yr{0.0f, 0.0f, 0.0f};
        glm::vec3 xr{0.0f, 0.0f, 0.0f};

        for (unsigned y = 0; y < height_; ++y) {

            // calculates vertical position of pixel
            if (y < half_height) {
                yr = down * -(y - half_height);
            } else if (y > half_height) {
                yr = up * (y - half_height);
            }

            for (unsigned x = 0; x < width_; ++x) {
                Pixel p(x, y);
                glm::vec3 pos = rotate_scene.camera_.position;

                // calculates horizontal position of pixel
                if (x < half_width) {
                    xr = l * -(x - half_width);
                } else if (x > half_width) {
                    xr = r * (x - half_width);
                }
                // final direction is the sum out of 3 directions of the viewplain
                //glm::vec3 direction = xr + yr + zr;
                // new for AntiAliasing
                std::vector<glm::vec3> directions;
                if (rotate_scene.antialiasing_ == 4) {
                    glm::vec3 dir_1 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.5f, y - (half_height) + 0.5f, -d});
                    glm::vec3 dir_2 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.5f, y - (half_height) - 0.5f, -d});
                    glm::vec3 dir_3 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.5f, y - (half_height) + 0.5f, -d});
                    glm::vec3 dir_4 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.5f, y - (half_height) - 0.5f, -d});
                    directions.push_back(dir_1);
                    directions.push_back(dir_2);
                    directions.push_back(dir_3);
                    directions.push_back(dir_4);

                } else if (rotate_scene.antialiasing_ == 8) {
                    glm::vec3 dir_1 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.5f, y - (half_height) + 0.5f, -d});
                    glm::vec3 dir_2 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.5f, y - (half_height) - 0.5f, -d});
                    glm::vec3 dir_3 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.5f, y - (half_height) + 0.5f, -d});
                    glm::vec3 dir_4 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.5f, y - (half_height) - 0.5f, -d});
                    glm::vec3 dir_5 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.25f, y - (half_height) + 0.25f, -d});
                    glm::vec3 dir_6 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.25f, y - (half_height) - 0.25f, -d});
                    glm::vec3 dir_7 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.25f, y - (half_height) + 0.25f, -d});
                    glm::vec3 dir_8 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.25f, y - (half_height) - 0.25f, -d});
                    directions.push_back(dir_1);
                    directions.push_back(dir_2);
                    directions.push_back(dir_3);
                    directions.push_back(dir_4);
                    directions.push_back(dir_5);
                    directions.push_back(dir_6);
                    directions.push_back(dir_7);
                    directions.push_back(dir_8);

                } else if (rotate_scene.antialiasing_ == 16) {
                    glm::vec3 dir_1 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.5f, y - (half_height) + 0.5f, -d});
                    glm::vec3 dir_2 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.5f, y - (half_height) - 0.5f, -d});
                    glm::vec3 dir_3 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.5f, y - (half_height) + 0.5f, -d});
                    glm::vec3 dir_4 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.5f, y - (half_height) - 0.5f, -d});
                    glm::vec3 dir_5 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.25f, y - (half_height) + 0.25f, -d});
                    glm::vec3 dir_6 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.25f, y - (half_height) - 0.25f, -d});
                    glm::vec3 dir_7 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.25f, y - (half_height) + 0.25f, -d});
                    glm::vec3 dir_8 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.25f, y - (half_height) - 0.25f, -d});
                    glm::vec3 dir_9 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.125f, y - (half_height) + 0.125f, -d});
                    glm::vec3 dir_10 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.125f, y - (half_height) - 0.125f, -d});
                    glm::vec3 dir_11 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.125f, y - (half_height) + 0.125f, -d});
                    glm::vec3 dir_12 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.125f, y - (half_height) - 0.125f, -d});
                    glm::vec3 dir_13 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.0625f, y - (half_height) + 0.0625f, -d});
                    glm::vec3 dir_14 = glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.0625f, y - (half_height) - 0.0625f, -d});
                    glm::vec3 dir_15 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.0625f, y - (half_height) + 0.0625f, -d});
                    glm::vec3 dir_16 = glm::normalize(
                            dir + glm::vec3{x - (half_width) - 0.0625f, y - (half_height) - 0.0625f, -d});
                    directions.push_back(dir_1);
                    directions.push_back(dir_2);
                    directions.push_back(dir_3);
                    directions.push_back(dir_4);
                    directions.push_back(dir_5);
                    directions.push_back(dir_6);
                    directions.push_back(dir_7);
                    directions.push_back(dir_8);
                    directions.push_back(dir_9);
                    directions.push_back(dir_10);
                    directions.push_back(dir_11);
                    directions.push_back(dir_12);
                    directions.push_back(dir_13);
                    directions.push_back(dir_14);
                    directions.push_back(dir_15);
                    directions.push_back(dir_16);

                } else if (rotate_scene.antialiasing_ == 1) {
                    //directions.push_back(glm::normalize(xr + yr + zr));
                    directions.push_back(glm::normalize(
                            dir + glm::vec3{x - (half_width) + 0.5f, y - (half_height) + 0.5f, -d}));
                }

                Pixel aliased;
                for (int i = 0; i < directions.size(); i++) {
                    // in dieser Schleife wird der Schnittpunkt mit dem ersten Objekt den der Strahl trifft berechnet
                    Hitpoint first_hit = fire_ray(rotate_scene, transformRay(Ray{pos, glm::normalize(directions[i])},
                                                                             rotate_scene.camera_.transformation_));

                    // Entweder es wurde ein Objekt getroffen oder der Pixel bekommt die Hintergrundfarbe zugewiesen
                    if (first_hit.hit_) {
                        Color raytracer_color = calc_color(first_hit, rotate_scene, 3);
                        tone_mapping(raytracer_color);
                        p.color = raytracer_color;
                    } else {
                        p.color = rotate_scene.backgroundcolor_;
                    }
                    aliased.color += p.color;
                }
                p.color = aliased.color / rotate_scene.antialiasing_;
                write(p);
            }
        }
        ppm_.save(picture_name);
        auto finish = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        printProgress(i, scene.frames, elapsed_time);
    }
}

void printProgress(int frame, int total, long time) {
    float progress = (float) (frame + 1) / (float) total;
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
    int val = (int) (progress * 100);
    int lpad = (int) (progress * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    float avg_time_left = (time * (1 / progress - 1)) / 60000;
    long avg_time_left_sec = (avg_time_left - floor(avg_time_left)) * 60;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    std::cout << " remaining: " << floor(avg_time_left) << "m" << avg_time_left_sec << "s";
    fflush(stdout);
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

// Farbwertberechnung, TODO !
Color Renderer::calc_color(Hitpoint const &hitpoint, Scene const &scene, unsigned int reflection_steps) {
    Color raytracer_value = Color(0.0f, 0.0f, 0.0f);
    Color ambient = calc_ambient(hitpoint.material_, scene);
    Color diffuse = calc_diffuse(hitpoint, scene);
    Color specular = calc_specular(hitpoint, scene);
    //TODO fix SegFault

    // Experimentelle Berechnung, durchsichtigkeit und Spiegelung nicht ausgereift
    if (hitpoint.material_->glossy_ > 0 && hitpoint.material_->opacity_ > 0) {           // transparent and reflactive
        float kr = calc_fresnel_reflection_ratio(hitpoint, scene);
        float ko = 1 - kr;
        Color reflection = calc_reflection(hitpoint, scene, reflection_steps);
        Color refraction = calc_refraction(hitpoint, scene, false, reflection_steps);
        raytracer_value = (kr * reflection + ko * refraction);
    } else if (hitpoint.material_->glossy_ > 0) {                                        // reflactive
        Color reflection = calc_reflection(hitpoint, scene, reflection_steps);
        Color phong = ambient + diffuse + specular;
        raytracer_value = (phong * (1 - hitpoint.material_->glossy_) + reflection * hitpoint.material_->glossy_);
    } //else if (hitpoint.material_->opacity_ > 0){} 
    else {                                                                              // default phong
        raytracer_value = (ambient + diffuse + specular);
    }
    tone_mapping(raytracer_value);                                                      // default tone mapping
    return raytracer_value;
}

// Diese Funktion ist in soweit fertig holt nur ka aus dem Material
Color Renderer::calc_ambient(std::shared_ptr<Material> material, Scene const &scene) {
    Color ambient = Color{scene.ambient_, scene.ambient_, scene.ambient_};
    return (material->ka_ * ambient);
}

// TODO fix graphical bug // maybe fixed
Color Renderer::calc_diffuse(Hitpoint const &hitpoint, Scene const &scene) {
    Color final{0, 0, 0};
    std::vector<Color> lights_color;
    for (auto light: scene.lights_) {
        bool light_not_visible = false;
        glm::vec3 cut_point;
        glm::vec3 new_normal;
        glm::vec3 vec_light_cut = glm::normalize(light.position_ - hitpoint.hitpoint_);

        //überprüfen ob zwischen objekt und Punktlichtquelle andere Objekte liegen
        for (auto shape : scene.shape_vector_) {
            light_not_visible = shape->intersect(Ray{hitpoint.hitpoint_ + 2.0f * hitpoint.normal_, vec_light_cut}).hit_;
            if (light_not_visible) {
                light_not_visible = true;
                break;  // if there is atleast one shape in between light and current shape light gets blocked
            }
        }
        // if there is no light blocking shape
        if (light_not_visible == false) {
            float o = glm::dot(vec_light_cut, glm::normalize(hitpoint.normal_));
            Color i_p = light.color_ * light.brightness_;
            Color k_d = hitpoint.material_->kd_;
            lights_color.push_back(k_d * i_p * o);
        }
    }
    for (auto color: lights_color) {
        final += color;
    }
    return final;
}

Color Renderer::calc_specular(Hitpoint const &hitpoint, Scene const &scene) {
    Color final{0, 0, 0};
    std::vector<Color> lights_color;
    for (auto light: scene.lights_) {
        bool light_not_visible = false;
        glm::vec3 cut_point;
        glm::vec3 new_normal;
        glm::vec3 vec_light_cut = glm::normalize(light.position_ - hitpoint.hitpoint_);

        //überprüfen ob zwischen objekt und Punktlichtquelle andere Objekte liegen
        for (auto shape : scene.shape_vector_) {
            light_not_visible = shape->intersect(Ray{hitpoint.hitpoint_ + 2.0f * hitpoint.normal_, vec_light_cut}).hit_;
            if (light_not_visible) {
                light_not_visible = true;
                break;  // if there is atleast one shape in between light and current shape light gets blocked
            }
        }
        // if there is no light blocking shape
        if (light_not_visible == false) {
            glm::vec3 camera_hitpoint = glm::normalize(camera_hitpoint - hitpoint.hitpoint_);
            glm::vec3 r = glm::dot(hitpoint.normal_, vec_light_cut) * 2.0f * hitpoint.normal_ - vec_light_cut;
            float p = abs(glm::dot(r, camera_hitpoint));
            float cos = pow(p, hitpoint.material_->m_);
            float m_pi = (hitpoint.material_->m_ + 2) / (2 * M_PI);
            Color i_p = light.color_ * light.brightness_;
            Color k_s = hitpoint.material_->ks_;
            lights_color.push_back(k_s * m_pi * cos * i_p);
        }
    }
    for (auto color: lights_color) {
        final += color;
    }
    return final;
}

// Working. No graphical testing yet
Color Renderer::calc_reflection(Hitpoint const &hitpoint, Scene const &scene, unsigned int recursive_boundary) {
    Color final{0, 0, 0};
    glm::vec3 incoming_direction = glm::normalize(hitpoint.direction_);
    glm::vec3 normal = glm::normalize(hitpoint.normal_);
    glm::vec3 reflaction_ray_direction = incoming_direction - 2 * (glm::dot(normal, incoming_direction)) * normal;
    Ray reflaction_ray{hitpoint.hitpoint_ + 1.0f, glm::normalize(reflaction_ray_direction)};
    Hitpoint next_hit = fire_ray(scene, reflaction_ray);

    // return of background color in case of no hit, no color in case of reaching maximum recursive depth
    if (!next_hit.hit_) {
        return scene.backgroundcolor_;
    } else {
        if (recursive_boundary > 0 && next_hit.hit_) {
            Color reflected_color = calc_color(next_hit, scene, recursive_boundary - 1) * 0.8f;
            return reflected_color;
        } else {
            return Color{0, 0, 0};
        }
    }
}

// calculates the refraction, not tested yet
Color
Renderer::calc_refraction(Hitpoint const &hitpoint, Scene const &scene, bool inside, unsigned int recursive_boundary) {
    float eta;

    // check if ray is coming from outside or inside the object
    if (inside) {
        eta = hitpoint.material_->refractive_index_;
    } else {
        eta = 1.0f / hitpoint.material_->refractive_index_;
    }

    // calculates cosi and inverts it if negative
    float cos1 = glm::dot(hitpoint.normal_, hitpoint.direction_);
    glm::vec3 n = hitpoint.normal_;
    if (cos1 < 0) {
        invert_direction(n);
    }

    // check for case of total reflection
    float sin2 = eta * sqrtf(std::max(0.0f, 1 - cos1 * cos1));
    if (sin2 > 1) {
        return calc_reflection(hitpoint, scene, recursive_boundary);
    }

    // calulating the refrected ray
    //float cos2 = sqrtf(1.0f - eta * eta * (1.0f - cos1 * cos1));
    //sglm::vec3 refrection_direction = eta * hitpoint.direction_ + (eta * cos1 - cos2) * hitpoint.normal_;
    glm::vec3 refrection_dir = glm::normalize(glm::refract(glm::normalize(hitpoint.direction_), glm::normalize(hitpoint.normal_), eta));
    glm::vec3 refrection_origin = hitpoint.hitpoint_ - 0.1f * hitpoint.normal_;
    Ray refrected_ray{refrection_origin, refrection_dir};

    // fires the refracted ray
    Hitpoint newhit = fire_ray(scene, refrected_ray);

    // if the new ray hitted the object again(from inside), another new object or non at all
    if (newhit.hit_ && hitpoint.name_ != newhit.name_) {
        return calc_color(newhit, scene, 3);
    } else if (newhit.hit_) {
        return calc_refraction(newhit, scene, true, recursive_boundary);
    } else {
        return scene.backgroundcolor_;
    }

}

float Renderer::calc_fresnel_reflection_ratio(Hitpoint const &hitpoint, Scene const &scene) {

    float cos1 = glm::clamp(-1.0f, 1.0f, glm::dot(hitpoint.direction_, hitpoint.normal_));
    float eta1 = 1;
    float eta2 = hitpoint.material_->refractive_index_;

    // check if inside or outside of object
    if (cos1 > 0) {
        std::swap(eta1, eta2);
    }
    float sin2 = (eta1 / eta2) * sqrtf(std::max(0.0f, 1 - cos1 * cos1));

    // check for case of total reflection
    if (sin2 > 1) {
        return 0;
    } else {
        float cos2 = sqrt(std::max(0.0f, 1 - sin2 * sin2));
        cos1 = fabsf(cos1);     // absolute value
        float n2cos1 = eta2 * cos1;
        float n1cos2 = eta1 * cos2;
        float f_parallel = (n2cos1 - n1cos2) / (n2cos1 + n1cos2);
        float f_perpendicular = (n1cos2 - n2cos1) / (n1cos2 + n2cos1);
        float ratio_of_reflected = 0.5 * (f_parallel + f_perpendicular);
        return ratio_of_reflected;
    }
}

Hitpoint Renderer::fire_ray(Scene const &scene, Ray const &ray) {
    Hitpoint first_hit;
    first_hit.distance_ = FLT_MAX;
    for (int i = 0; i < scene.shape_vector_.size(); ++i) {
        Hitpoint hit = scene.shape_vector_[i]->intersect(ray);
        if (hit.hit_ && hit.distance_ < first_hit.distance_) {
            first_hit = hit;
        }
    }
    return first_hit;
}

// inverts a direction
void Renderer::invert_direction(glm::vec3 &dir) {
    dir = dir * -1.0f;
}

// Diese Funktion macht am Ende das tone mapping
void Renderer::tone_mapping(Color &color) {
    color.r = color.r / (color.r + 1);
    color.g = color.g / (color.g + 1);
    color.b = color.b / (color.b + 1);
}
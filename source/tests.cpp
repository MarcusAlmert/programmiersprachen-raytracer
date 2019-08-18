#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <memory>
#include "shapes/shape.hpp"
#include "shapes/sphere.hpp"
#include "shapes/box.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <renderer.hpp>
#include "material.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "shapes/composite.hpp"


int main(int argc, char *argv[]) {

    return Catch::Session().run(argc, argv);

}

/* Tests for Shapes */

TEST_CASE("Material print", "Material") {
    Material red{"Red", Color{1, 1, 1}, Color{0, 0, 0}, Color{0.5, 0.5, 0.5}, 1.0f};
    std::cout << red << std::endl;
}

TEST_CASE("Sphere standard Constructor", "[Sphere]") {
    Sphere sp1 = Sphere();
    CHECK(sp1.area() == 0);
    CHECK(sp1.volume() == 0);
}

TEST_CASE("Sphere Constructor", "[Sphere]") {
    Sphere sp1 = Sphere({1, 1, 1}, 10);
    CHECK(sp1.area() == Approx(1256.637));
    CHECK(sp1.volume() == Approx(4188.79));
}


TEST_CASE("Sphere area()", "[Sphere]") {
    Sphere sp1 = Sphere({3, 4, 10}, 13);
    CHECK(sp1.area() == Approx(2123.717));
    sp1 = Sphere({2, 3, 1}, 2);
    CHECK(sp1.area() == Approx(50.265));
    sp1 = Sphere({2, 3, 1}, 0);
    CHECK(sp1.area() == Approx(0));
}

TEST_CASE("Sphere volume()", "[Sphere]") {
    Sphere sp1 = Sphere({3, 4, 10}, 13);
    CHECK(sp1.volume() == Approx(9202.772));
    sp1 = Sphere({2, 3, 1}, 2);
    CHECK(sp1.volume() == Approx(33.51));
    sp1 = Sphere({2, 3, 1}, 0);
    CHECK(sp1.volume() == Approx(0));
}

TEST_CASE("Box standard Constructor", "[Box]") {
    Box b1 = Box();
    CHECK(b1.area() == 0);
    CHECK(b1.volume() == 0);
}

TEST_CASE("Box Constructor", "[Box]") {
    Box b1 = Box({0, 0, 0}, {10, 10, 10});
    CHECK(b1.area() == Approx(600));
    CHECK(b1.volume() == Approx(1000));
}


TEST_CASE("Box volume()", "[Box]") {
    Box b1 = Box({0, 0, 0}, {10, 10, 10});
    CHECK(b1.volume() == Approx(1000));
    b1 = Box({10, 10, 10}, {0, 0, 0});
    CHECK(b1.volume() == Approx(1000));
    b1 = Box({12, 11, 3}, {1, 10, 23});
    CHECK(b1.volume() == Approx(220));
}

TEST_CASE("Box area()", "[Box]") {
    Box b1 = Box({0, 0, 0}, {10, 10, 10});
    CHECK(b1.area() == Approx(600));
    b1 = Box({10, 10, 10}, {0, 0, 0});
    CHECK(b1.area() == Approx(600));
    b1 = Box({12, 11, 3}, {1, 10, 23});
    CHECK(b1.area() == Approx(502.0));
}

TEST_CASE("Print", "[Shapes]") {
    Box b1{{1, 1, 1},
           {0, 0, 0}};
    Sphere sp1;
    std::cout << "--------- test ------------\n";
    sp1.print(std::cout) << std::endl;
    b1.print(std::cout);
    std::cout << "---------test over----------\n";
}


TEST_CASE ("intersect_ray_sphere", "[intersect]") {
// Ray
    glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
// ray direction has to be normalized !
// you can use :
// v = glm :: normalize ( some_vector )
    glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};
// Sphere
    glm::vec3 sphere_center{0.0f, 0.0f, 5.0f};
    float sphere_radius{1.0f};
    float distance = 0.0f;
    auto result = glm::intersectRaySphere(
            ray_origin, ray_direction,
            sphere_center,
            sphere_radius * sphere_radius, // squared radius !!!
            distance);
    CHECK (distance == Approx(4.0f));


    Sphere s1{glm::vec3{5.0f, 5.0f, 5.0f}, 1.0f};
    Sphere s2{glm::vec3{10.0f, 10.0f, 10.0f}, 1.0f};
    Ray ray{{0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f}};
    Ray raymissed{{0.0f, 0.0f,  0.0f},
                  {0.0f, -1.0f, 0.0f}};
    Hitpoint hit = s1.intersect(ray);
    Hitpoint missed = s2.intersect(raymissed);

    CHECK(hit.hit_);
    CHECK(hit.name_ == "No_name");
    CHECK(!missed.hit_);
    CHECK(missed.name_ == "miss");
}

TEST_CASE("Aufgabe 5.8", "Shape") {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    Sphere *s1 = new Sphere{position, 1.2f};
    Shape *s2 = new Sphere{position, 1.2f};
    s1->print(std::cout);
    s2->print(std::cout);
    delete s1;
    delete s2;
}

//TODO more test cases
TEST_CASE("Aufgabe 6.3 intersect ray-box", "Box") {
    Box b1{{0,  0,  0},
           {10, 10, 10}};
    Ray orig{{20, 5, 5},
             {-1, 0, 0}};
    Hitpoint hitp = b1.intersect(orig);
    CHECK(hitp.hit_);
    CHECK(hitp.hitpoint_.x == 10);
    CHECK(hitp.hitpoint_.y == 5);
    CHECK(hitp.hitpoint_.z == 5);
}

TEST_CASE("More intersect tests for boxes", "[intersect,Box]"){
    Box b1{glm::vec3{0, 0, 0}, glm::vec3{10, 10, 10}};
    Ray r1{glm::vec3{5, 20, 5}, glm::vec3{0, -1, 0}};
    Hitpoint hitp = b1.intersect(r1);
    CHECK(hitp.hit_);
    CHECK(hitp.hitpoint_.x == 5);
    CHECK(hitp.hitpoint_.y == 10);
    CHECK(hitp.hitpoint_.z == 5);
    Ray r2{glm::vec3{30, 30, 30}, glm::vec3{-1, -1, -1}};
    Hitpoint hitp1 = b1.intersect(r2);
    CHECK(hitp1.hit_);
    CHECK(hitp1.hitpoint_.x == 10);
    CHECK(hitp1.hitpoint_.y == 10);
    CHECK(hitp1.hitpoint_.z == 10);
}

TEST_CASE("read sdf", "SDF") {
    Scene scene1 = read_sdf("../../SDF-Scene/example.sdf");
    auto vec = scene1.mat_vector_;
    CHECK(scene1.mat_vector_[0]->name_ == "red");
    std::shared_ptr<Material> red = scene1.mat_vector_[0];
    CHECK(red->ka_.r == 1);
    CHECK(red->ka_.g == 0);
    CHECK(red->ka_.b == 0);
    CHECK(red->kd_.r == 1);
    CHECK(red->kd_.g == 0);
    CHECK(red->kd_.b == 0);
    CHECK(red->ks_.r == 1);
    CHECK(red->ks_.g == 0);
    CHECK(red->ks_.b == 0);
    CHECK(red->m_ == 20);
    CHECK(red->glossy_ == 1);
    CHECK(red->opacity_ == 2);
    CHECK(red->refractive_index_ == 3);
    CHECK(scene1.mat_vector_[1]->name_ == "green");
    std::shared_ptr<Material> green = scene1.mat_vector_[1];
    CHECK(green->ka_.r == 0);
    CHECK(green->ka_.g == 1);
    CHECK(green->ka_.b == 0);
    CHECK(green->kd_.r == 0);
    CHECK(green->kd_.g == 1);
    CHECK(green->kd_.b == 0);
    CHECK(green->ks_.r == 0);
    CHECK(green->ks_.g == 1);
    CHECK(green->ks_.b == 0);
    CHECK(green->m_ == 50);
    CHECK(green->glossy_ == 4);
    CHECK(green->opacity_ == 5);
    CHECK(green->refractive_index_ == 6);
    CHECK(scene1.mat_vector_[2]->name_ == "blue");
    std::shared_ptr<Material> blue = scene1.mat_vector_[2];
    CHECK(blue->ka_.r == 0);
    CHECK(blue->ka_.g == 0);
    CHECK(blue->ka_.b == 1);
    CHECK(blue->kd_.r == 0);
    CHECK(blue->kd_.g == 0);
    CHECK(blue->kd_.b == 1);
    CHECK(blue->ks_.r == 0);
    CHECK(blue->ks_.g == 0);
    CHECK(blue->ks_.b == 1);
    CHECK(blue->m_ == 10);
    CHECK(blue->glossy_ == 7);
    CHECK(blue->opacity_ == 8);
    CHECK(blue->refractive_index_ == 9);
    CHECK(scene1.shape_vector_[0]->name_ == "sphere1");
    CHECK(scene1.shape_vector_[0]->material_->name_ == "red");
    CHECK(scene1.shape_vector_[1]->material_->name_ == "blue");
    std::cout << *scene1.shape_vector_[0];
    std::cout << *scene1.shape_vector_[1];
    CHECK(scene1.shape_vector_[1]->name_ == "box1");
    CHECK(scene1.lights_[0].name_ == "licht");
    CHECK(scene1.lights_[0].brightness_ == 50);
    CHECK(scene1.lights_[0].color_.r == 0.5f);
    CHECK(scene1.lights_[0].color_.g == 0.1f);
    CHECK(scene1.lights_[0].color_.b == 0.3f);
    CHECK(scene1.lights_[0].position_.x == 10);
    CHECK(scene1.lights_[0].position_.y == 10);
    CHECK(scene1.lights_[0].position_.z == 5);
    CHECK(scene1.camera_.name == "eye");
    CHECK(scene1.camera_.fov == 60);
    CHECK(scene1.camera_.position.x == 0);
    CHECK(scene1.camera_.position.y == 0);
    CHECK(scene1.camera_.position.z == 0);
    CHECK(scene1.ambient_ == 0.112f);
    CHECK(scene1.camera_.direction.x == 0);
    CHECK(scene1.camera_.direction.y == 0);
    CHECK(scene1.camera_.direction.z == -1);
    CHECK(scene1.camera_.upVector.x == 0);
    CHECK(scene1.camera_.upVector.y == 1);
    CHECK(scene1.camera_.upVector.z == 0);
}
// new with cylinder, cone , triangle  and composite starts here
TEST_CASE("Testcase SDF-Reader for new shapes") {
    Scene scene = read_sdf("../../SDF-Scene/composite.sdf");
    CHECK(scene.ambient_ == 0.1f);
    CHECK(scene.shape_vector_[0]->name_ == "rbox");
    CHECK(scene.shape_vector_[1]->name_ == "bsphere");
    CHECK(scene.shape_vector_[2]->name_ == "bcylinder");
    std::cout << scene.shape_vector_[2]->name_;
    CHECK(scene.shape_vector_[3]->name_ == "rcone");
    CHECK(scene.shape_vector_[4]->name_ == "gtriangle");
    CHECK(scene.shape_vector_[5]->name_ == "root");
}

TEST_CASE("find()", "vec,map,set") {
    Scene scene1 = read_sdf("../../SDF-Scene/example.sdf");
    auto vec = scene1.mat_vector_;
    CHECK(find(vec, "red")->name_ == "red");
}

TEST_CASE("struct Light, print", "[Light]"){
    Light l1{"Testlicht", glm::vec3{0, 0, 0}, Color{0.0f, 0.0f, 0.0f}, 0.0f};
    std::cout << l1 << std::endl;
    CHECK(true);
}

TEST_CASE("struct Hitpoint, print", "[Hitpoint]"){
    Hitpoint h1;
    std::shared_ptr<Material> mat = std::make_shared<Material>(Material{});

    Hitpoint h2{true, 550.0f, "Peter", mat, glm::vec3{1, 1, 1}, glm::vec3{1, 1, 1}, glm::vec3{1, 1, 1}};
    std::cout << h1 << h2 << std::endl;
    CHECK(true);
}

/*TEST_CASE("Simple_renderer Test"){
    Scene scene1 = read_sdf("../../SDF-Scene/example.sdf");
    Renderer test_renderer(600,600,"./test_ppm_example");
    test_renderer.render(scene1);
}*/

//TODO make tests for composite, cone, triangle and cylinder
TEST_CASE("Composite functions", "Composite") {

}

TEST_CASE("Cylinder functions", "Cylinder") {

}

TEST_CASE("Cone functions", "Cone") {

}

TEST_CASE("Triangle functions", "Triangle") {

}


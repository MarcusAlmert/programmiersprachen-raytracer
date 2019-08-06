#define CATCH_CONFIG_RUNNER

#include <catch.hpp>
#include <memory>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "material.hpp"
#include "scene.hpp"
#include "light.hpp"

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

    CHECK(hit.hit);
    CHECK(hit.name == "No_name");
    CHECK(!missed.hit);
    CHECK(missed.name == "miss");
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
    CHECK(hitp.hit);
    CHECK(hitp.hitpoint.x == 10);
    CHECK(hitp.hitpoint.y == 5);
    CHECK(hitp.hitpoint.z == 5);
}

TEST_CASE("More intersect tests for boxes", "[intersect,Box]"){
    Box b1{glm::vec3{0, 0, 0}, glm::vec3{10, 10, 10}};
    Ray r1{glm::vec3{5, 20, 5}, glm::vec3{0, -1, 0}};
    Hitpoint hitp = b1.intersect(r1);
    CHECK(hitp.hit);
    CHECK(hitp.hitpoint.x == 5);
    CHECK(hitp.hitpoint.y == 10);
    CHECK(hitp.hitpoint.z == 5);
    Ray r2{glm::vec3{30, 30, 30}, glm::vec3{-1, -1, -1}};
    Hitpoint hitp1 = b1.intersect(r2);
    CHECK(hitp1.hit);
    CHECK(hitp1.hitpoint.x == 10);
    CHECK(hitp1.hitpoint.y == 10);
    CHECK(hitp1.hitpoint.z == 10);
}

TEST_CASE("read sdf", "SDF") {
    Scene scene1 = read_sdf("../../SDF-Scene/example.sdf");
    auto vec = scene1.mat_vector;
    CHECK(scene1.mat_vector[0]->name == "red");
    CHECK(scene1.mat_vector[1]->name == "green");
    CHECK(scene1.mat_vector[2]->name == "blue");
    CHECK(scene1.shape_vector[0]->name == "sphere1");
    CHECK(scene1.shape_vector[0]->material->name == "red");
    CHECK(scene1.shape_vector[1]->material->name == "blue");
    std::cout << *scene1.shape_vector[0];
    std::cout << *scene1.shape_vector[1];
    CHECK(scene1.shape_vector[1]->name == "box1");
    CHECK(scene1.lights[0].name_ == "licht");
    CHECK(scene1.lights[0].brightness_ == 50);
    CHECK(scene1.lights[0].color_.r == 0.5f);
    CHECK(scene1.lights[0].color_.g == 0.1f);
    CHECK(scene1.lights[0].color_.b == 0.3f);
    CHECK(scene1.lights[0].position_.x == 10);
    CHECK(scene1.lights[0].position_.y == 10);
    CHECK(scene1.lights[0].position_.z == 5);
    CHECK(scene1.cam.name == "eye");
    CHECK(scene1.cam.fov == 60);
    CHECK(scene1.cam.position.x == 0);
    CHECK(scene1.cam.position.y == 0);
    CHECK(scene1.cam.position.z == 0);
    CHECK(scene1.ambient == 0.112f);
}

TEST_CASE("find()", "vec,map,set") {
    Scene scene1 = read_sdf("../../SDF-Scene/example.sdf");
    auto vec = scene1.mat_vector;
    CHECK(find(vec, "red")->name == "red");
}

TEST_CASE("struct Light, print", "[Light]"){
    Light l1{"Testlicht", glm::vec3{0, 0, 0}, Color{0.0f, 0.0f, 0.0f}, 0.0f};
    std::cout << l1 << std::endl;
    CHECK(true);
}
#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "../framework/read_sdf.hpp"
#include <chrono>

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    Scene scene = read_sdf("../../SDF-Scene/ppoint.sdf");   // alle lieben relative Pfade

    unsigned const image_width = scene.width;
    unsigned const image_height = scene.height;
    std::string const filename = scene.filename;
    Renderer renderer{image_width, image_height, filename};

    //create separate thread to see updates of pixels while rendering
    //std::thread render_thread([&renderer]() {renderer.render();});

    // dem renderer wird hier die eingelesene Szene gegeben
    renderer.render(scene);

    auto finish = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    float min = (float) elapsed_time / 60000.0f;
    long sec = (min - floor(min)) * 60;
    std::cout << "\nelapsed time: " << floor(min) << "m" << sec << "s";

    Window window{{image_width, image_height}};

    while (!window.should_close()) {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            window.close();
        }
        window.show(renderer.color_buffer());
    }

    //"join" threads, i.e. synchronize main thread with render_thread
    //render_thread.join();

    return 0;
}

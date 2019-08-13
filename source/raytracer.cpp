#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "../framework/read_sdf.cpp"

int main(int argc, char* argv[])
{
  unsigned const image_width = 500;
  unsigned const image_height = 500;
  std::string const filename = "./Test.ppm";  // Unsere Bilder werden in Test.ppm gespeichert

  Renderer renderer{image_width, image_height, filename};

  Scene scene = read_sdf("../../SDF-Scene/test2.sdf");   // alle lieben relative Pfade

  //create separate thread to see updates of pixels while rendering
  //std::thread render_thread([&renderer]() {renderer.render();});

  // dem renderer wird hier die eingelesene Szene gegeben
  renderer.render(scene);

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

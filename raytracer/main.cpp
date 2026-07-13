// Standalone renderer for the P4_raytracer capstone.
//
// This is NOT part of cpplings' automatic exercise discovery (it lives outside
// the exercises/ tree, so the CMake glob never touches it). It lets you render
// ANY scene file to a PNG using YOUR OWN completed exercise code.
//
// How it works: it #includes your exercise source with DOCTEST_CONFIG_DISABLE,
// which strips every TEST_CASE and doctest's own main(), leaving just the ray
// tracer classes (parse_scene, Camera, Renderer, Image, ...) for us to drive
// from a real main(). It therefore only produces good images once you have
// filled in all the TODOs.
//
// Build (from this directory):
//   g++ -std=c++23 -O2 -DDOCTEST_CONFIG_DISABLE -I../external/doctest \
//       main.cpp -o raytrace
//
// Run (scene file first, output PNG second):
//   ./raytrace ../exercises/05_capstone/scenes/cornell.txt cornell.png
//   ./raytrace ../exercises/05_capstone/scenes/spheres.txt spheres.png

#define DOCTEST_CONFIG_DISABLE
#include "../exercises/05_capstone/P4_raytracer.cpp"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "usage: " << argv[0] << " <scene.txt> <output.png>\n";
    return 1;
  }

  const std::string scene_file = argv[1];
  const std::string output_file = argv[2];

  try {
    // 1. Read the scene from the text file.
    ParsedScene parsed = parse_scene(scene_file);

    // 2. Build the camera and renderer.
    Camera camera(parsed.camera.eye, parsed.camera.look_at, parsed.camera.up,
                  parsed.camera.fov, parsed.width, parsed.height);
    Renderer renderer(parsed.scene);

    // 3. Render, one primary ray per pixel.
    Image image(parsed.width, parsed.height);
    for (int y = 0; y < parsed.height; ++y) {
      for (int x = 0; x < parsed.width; ++x) {
        double s = (x + 0.5) / parsed.width;
        double t = (y + 0.5) / parsed.height;
        image.set(x, y, renderer.trace(camera.ray_through(s, t), 0));
      }
      std::cout << "\rrendering... " << (100 * (y + 1) / parsed.height) << '%' << std::flush;
    }
    std::cout << '\n';

    // 4. Write the PNG.
    if (!image.save_png(output_file)) {
      std::cerr << "error: could not write " << output_file << '\n';
      return 1;
    }
    std::cout << "wrote " << output_file << '\n';
  } catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}

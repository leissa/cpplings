# Capstone project: a ray tracer

The concluding project of the course. You build a small
[**ray tracer**](<https://en.wikipedia.org/wiki/Ray_tracing_(graphics)>) that
renders 3D scenes of spheres and triangles into a
[PNG](https://en.wikipedia.org/wiki/PNG) image, with
[Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) lighting,
[shadows](https://en.wikipedia.org/wiki/Ray_casting) and
[mirror reflections](<https://en.wikipedia.org/wiki/Reflection_(computer_graphics)>).

It pulls together most of the course:

- **classes** and **overloaded operators** (`Vec3`)
- **inheritance** with **virtual methods** (`Object` → `Sphere`, `Triangle`)
- `std::optional`, `std::unique_ptr`, `std::vector`
- recursion (mirror reflections)

Everything lives in a single file, `P4_raytracer.cpp`.

## What you have to do

Work through **PART 1 → PART 10** in order (later parts use earlier ones). Each
part has a `// TODO` with a precise description of the function to implement,
followed by the `TEST_CASE`s that check it.

| Part | You implement                                                                   | Background                                                                                                                                                                                                                                                                                      |
| ---- | ------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1    | `Vec3` — operators `+ - * /`, unary `-`, `dot`, `cross`, `length`, `normalized` | [vector](https://en.wikipedia.org/wiki/Euclidean_vector), [dot](https://en.wikipedia.org/wiki/Dot_product) / [cross product](https://en.wikipedia.org/wiki/Cross_product), [norm](<https://en.wikipedia.org/wiki/Norm_(mathematics)>), [unit vector](https://en.wikipedia.org/wiki/Unit_vector) |
| 2    | `reflect(d, n)`                                                                 | [specular reflection](https://en.wikipedia.org/wiki/Specular_reflection#Direction_of_reflection)                                                                                                                                                                                                |
| 3    | `Ray::at`                                                                       | [line/ray](<https://en.wikipedia.org/wiki/Line_(geometry)#Ray>)                                                                                                                                                                                                                                 |
| 4    | `Object` base + `Sphere::intersect` (ray–sphere quadratic)                      | [line–sphere intersection](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection), [quadratic formula](https://en.wikipedia.org/wiki/Quadratic_formula)                                                                                                                                |
| 5    | `Triangle::intersect` (Möller–Trumbore)                                         | [Möller–Trumbore](https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm), [barycentric coords](https://en.wikipedia.org/wiki/Barycentric_coordinate_system)                                                                                                         |
| 6    | `Camera` (basis in the constructor + `ray_through`)                             | [pinhole camera](https://en.wikipedia.org/wiki/Pinhole_camera_model), [field of view](https://en.wikipedia.org/wiki/Field_of_view)                                                                                                                                                              |
| 7    | `Scene::closest_hit` and `Scene::in_shadow`                                     | [surface normal](<https://en.wikipedia.org/wiki/Normal_(geometry)>), [ray casting](https://en.wikipedia.org/wiki/Ray_casting)                                                                                                                                                                   |
| 8    | `Renderer::shade` (Phong: ambient + diffuse + specular)                         | [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model), [Lambertian](https://en.wikipedia.org/wiki/Lambertian_reflectance)                                                                                                                                              |
| 9    | `Renderer::trace` (recursion + mirror reflection)                               | [recursive ray tracing](<https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Recursive_ray_tracing_algorithm>)                                                                                                                                                                                 |
| 10   | _(nothing to write)_ — renders `scenes/test.txt` to `out.png`                   | [gamma correction](https://en.wikipedia.org/wiki/Gamma_correction)                                                                                                                                                                                                                              |

**Do not modify** the `TEST_CASE`s, nor the two blocks marked
`GIVEN ... (do not modify)` — the **PNG encoder** and the **scene-file parser**.
They are provided so you can focus on the ray tracer itself.

## How to run it

From the **cpplings repo root** (this is important — PART 10 reads
`exercises/05_capstone/scenes/test.txt` by a path relative to the repo root):

```sh
./cpplings run P4_raytracer     # build + run once
./cpplings watch P4_raytracer   # rebuild automatically as you edit
```

You start with all 10 tests failing. Fill in the TODOs until they pass. When
PART 10 passes it writes **`out.png`** into the current directory — open it to
see your render!

## Rendering the other scenes

The exercise itself only renders one small scene (`scenes/test.txt`, chosen so
its result is easy to check automatically). To render the bigger, prettier
scenes, use the standalone renderer in the sibling `raytracer/` folder. It reuses
**your own completed `P4_raytracer.cpp`**, so it only works once your TODOs are
done.

```sh
cd raytracer
g++ -std=c++23 -O2 -I../external/doctest main.cpp -o raytrace
./raytrace ../exercises/05_capstone/scenes/cornell.txt cornell.png
```

Bundled scenes (in `scenes/`):

| Scene         | Shows                                                                |
| ------------- | -------------------------------------------------------------------- |
| `test.txt`    | The tiny scene graded by PART 10 (a red sphere on a sky background). |
| `example.txt` | Three spheres on a reflective floor.                                 |
| `cornell.txt` | A Cornell box built from triangles; mirror + glossy spheres.         |
| `pyramid.txt` | A triangle pyramid and two spheres on a reflective floor.            |
| `spheres.txt` | Five spheres with increasing shininess/reflectivity, mirror floor.   |
| `mirrors.txt` | Two facing mirror walls — a hall-of-mirrors effect.                  |

## Scene description language

One command per line; `#` starts a comment. Colours are RGB in `[0, 1]`.

| Command      | Arguments                                                    |
| ------------ | ------------------------------------------------------------ |
| `size`       | `width height`                                               |
| `camera`     | `eye(x y z) lookat(x y z) up(x y z) fov`                     |
| `background` | `r g b`                                                      |
| `ambient`    | `r g b`                                                      |
| `light`      | `pos(x y z) color(r g b)`                                    |
| `material`   | `name diffuse(r g b) specular(r g b) shininess reflectivity` |
| `sphere`     | `center(x y z) radius material`                              |
| `triangle`   | `v0(x y z) v1(x y z) v2(x y z) material`                     |

Make your own scenes and render them the same way!

## Further reading (Wikipedia)

Concepts, roughly in the order you meet them:

- Linear algebra: [Euclidean vector](https://en.wikipedia.org/wiki/Euclidean_vector),
  [dot product](https://en.wikipedia.org/wiki/Dot_product),
  [cross product](https://en.wikipedia.org/wiki/Cross_product),
  [norm / length](<https://en.wikipedia.org/wiki/Norm_(mathematics)>),
  [unit vector](https://en.wikipedia.org/wiki/Unit_vector),
  [surface normal](<https://en.wikipedia.org/wiki/Normal_(geometry)>).
- Rays & intersections:
  [line–sphere intersection](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection),
  [Möller–Trumbore ray–triangle](https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm),
  [barycentric coordinates](https://en.wikipedia.org/wiki/Barycentric_coordinate_system),
  [quadratic formula](https://en.wikipedia.org/wiki/Quadratic_formula).
- Reflection: [specular reflection](https://en.wikipedia.org/wiki/Specular_reflection#Direction_of_reflection),
  [reflection in computer graphics](<https://en.wikipedia.org/wiki/Reflection_(computer_graphics)>).
- Lighting: [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model),
  [Phong shading](https://en.wikipedia.org/wiki/Phong_shading),
  [Lambertian reflectance](https://en.wikipedia.org/wiki/Lambertian_reflectance).
- Camera & rendering: [pinhole camera model](https://en.wikipedia.org/wiki/Pinhole_camera_model),
  [field of view](https://en.wikipedia.org/wiki/Field_of_view),
  [ray casting](https://en.wikipedia.org/wiki/Ray_casting),
  [ray tracing](<https://en.wikipedia.org/wiki/Ray_tracing_(graphics)>).
- Output: [PNG](https://en.wikipedia.org/wiki/PNG),
  [gamma correction](https://en.wikipedia.org/wiki/Gamma_correction).

## Ideas to go further

- [**Anti-aliasing**](https://en.wikipedia.org/wiki/Supersampling): shoot several
  jittered rays per pixel and average them — the current renderer uses one ray
  per pixel, so edges are jagged.
- More shapes (planes, boxes), or
  [transparency / refraction](https://en.wikipedia.org/wiki/Snell%27s_law).

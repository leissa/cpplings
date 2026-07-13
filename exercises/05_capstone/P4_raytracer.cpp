// project: raytracer
//
// The grand finale: build a small ray tracer that renders 3D spheres and
// triangles into a PNG image, with Phong lighting, shadows and mirror
// reflections. It pulls together everything from the course: classes,
// overloaded operators, inheritance with virtual methods, std::optional,
// std::unique_ptr and std::vector.
//
// Work through each PART in order; later parts use earlier ones. When every
// part is done, PART 10 renders exercises/05_capstone/scenes/test.txt and writes
// "out.png" into the current directory. Open it and admire your work!
// (To render the other bundled scenes, see this folder's README.md.)
//
//   RUN THIS EXERCISE FROM THE cpplings REPO ROOT (that is where the normal
//   ./cpplings runner starts), otherwise the render test cannot find scene.txt.
//
// Do not modify the TEST_CASEs.
// Do not modify the blocks marked "GIVEN ... (do not modify)"; they are the
// PNG encoder and the scene-file parser, which are not the point of this
// exercise.

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <doctest/doctest.h>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <numbers>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

// ============================================================================
// PART 1: Vec3 - a 3D vector, used for points, directions AND colours.
// ============================================================================
// TODO: Implement all the member and free functions below. The fields and the
// constructors are given. Each function has a one-line description; fill in the
// body so the arithmetic works as you would expect for vectors.
class Vec3 {
public:
  double x = 0.0, y = 0.0, z = 0.0;
  Vec3() = default;
  Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

  // Negation:  -v
  Vec3 operator-() const { return {}; } // TODO
  // Vector addition / subtraction:  a + b ,  a - b
  Vec3 operator+(const Vec3 &v) const { return {}; } // TODO
  Vec3 operator-(const Vec3 &v) const { return {}; } // TODO
  // Component-wise product (handy for modulating colours):  a * b
  Vec3 operator*(const Vec3 &v) const { return {}; } // TODO
  // Scaling by a scalar:  v * s   and   v / s
  Vec3 operator*(double s) const { return {}; } // TODO
  Vec3 operator/(double s) const { return {}; } // TODO
  // Compound addition:  a += b   (return *this)
  Vec3 &operator+=(const Vec3 &v) { return *this; } // TODO
  // Squared length, length, and a unit vector in the same direction.
  double length_squared() const { return 0.0; } // TODO
  double length() const { return 0.0; }          // TODO: use length_squared()
  Vec3 normalized() const { return {}; }         // TODO: this / length()
};
// scalar * vector (so both v*s and s*v work). TODO: return v * s
inline Vec3 operator*(double s, const Vec3 &v) { return {}; }
// Dot product. TODO
inline double dot(const Vec3 &a, const Vec3 &b) { return 0.0; }
// Cross product. TODO:  (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx)
inline Vec3 cross(const Vec3 &a, const Vec3 &b) { return {}; }

TEST_CASE("Part 1: Vec3") {
  Vec3 a(1, 2, 3), b(4, 5, 6);
  CHECK((a + b).x == doctest::Approx(5));
  CHECK((b - a).y == doctest::Approx(3));
  CHECK((a * 2.0).z == doctest::Approx(6));
  CHECK((2.0 * a).x == doctest::Approx(2));
  CHECK((b / 2.0).x == doctest::Approx(2));
  CHECK((-a).y == doctest::Approx(-2));
  CHECK(dot(a, b) == doctest::Approx(32));
  Vec3 c = cross(Vec3(1, 0, 0), Vec3(0, 1, 0));
  CHECK(c.x == doctest::Approx(0));
  CHECK(c.y == doctest::Approx(0));
  CHECK(c.z == doctest::Approx(1));
  CHECK(Vec3(3, 4, 0).length() == doctest::Approx(5));
  Vec3 n = Vec3(0, 3, 4).normalized();
  CHECK(n.length() == doctest::Approx(1));
  CHECK(n.y == doctest::Approx(0.6));
}

// ============================================================================
// PART 2: reflect - mirror a direction about a surface normal.
// ============================================================================
// TODO: Implement the classic reflection formula:  r = d - 2 (d . n) n
// (n is assumed to be a unit vector.)
inline Vec3 reflect(const Vec3 &d, const Vec3 &n) { return {}; } // TODO

TEST_CASE("Part 2: reflect") {
  Vec3 r = reflect(Vec3(0, -1, 0), Vec3(0, 1, 0));
  CHECK(r.x == doctest::Approx(0));
  CHECK(r.y == doctest::Approx(1));
  CHECK(r.z == doctest::Approx(0));
  Vec3 r2 = reflect(Vec3(1, -1, 0), Vec3(0, 1, 0));
  CHECK(r2.x == doctest::Approx(1));
  CHECK(r2.y == doctest::Approx(1));
}

// ============================================================================
// PART 3: Ray - a half-line  origin + t * direction  (t >= 0).
// ============================================================================
class Ray {
public:
  Vec3 origin, direction; // direction is kept normalized by the constructor
  Ray() = default;
  Ray(const Vec3 &origin, const Vec3 &direction)
      : origin(origin), direction(direction.normalized()) {}
  // TODO: return the point at parameter t along the ray:  origin + direction * t
  Vec3 at(double t) const { return {}; } // TODO
};

TEST_CASE("Part 3: Ray") {
  Ray ray(Vec3(1, 2, 3), Vec3(0, 0, 5));
  CHECK(ray.direction.z == doctest::Approx(1)); // normalized
  Vec3 p = ray.at(2.0);
  CHECK(p.x == doctest::Approx(1));
  CHECK(p.z == doctest::Approx(5));
}

// --- GIVEN: Material, Light, Hit (do not modify) ----------------------------
struct Material {
  Vec3 diffuse = Vec3(0.8, 0.8, 0.8);  // base colour under direct light
  Vec3 specular = Vec3(1.0, 1.0, 1.0); // colour of the shiny highlight
  double shininess = 32.0;             // Phong exponent (bigger = tighter)
  double reflectivity = 0.0;           // 0 = matte, 1 = perfect mirror
};
struct Light {
  Vec3 position;
  Vec3 color = Vec3(1, 1, 1);
};
struct Hit {
  double t;    // ray parameter at the intersection
  Vec3 point;  // world-space intersection point
  Vec3 normal; // unit surface normal at that point
  Material material;
};

// ============================================================================
// PART 4: Object base class + Sphere::intersect
// ============================================================================
// Object is the abstract base class for anything a ray can hit. Sphere and
// Triangle override intersect(). This is the classic polymorphism pattern: the
// renderer only ever talks to Object. The base class is given.
class Object {
public:
  Material material;
  explicit Object(const Material &material) : material(material) {}
  virtual ~Object() = default;
  // Return the closest hit with t in (t_min, t_max), or std::nullopt on a miss.
  virtual std::optional<Hit> intersect(const Ray &ray, double t_min, double t_max) const = 0;
};

class Sphere : public Object {
public:
  Vec3 center;
  double radius;
  Sphere(const Vec3 &center, double radius, const Material &material)
      : Object(material), center(center), radius(radius) {}

  // TODO: Ray-sphere intersection.
  // Substitute the ray into |p - center|^2 = radius^2 to get a quadratic
  // a t^2 + b t + c = 0 with:
  //     oc = ray.origin - center
  //     a  = dot(direction, direction)
  //     b  = 2 * dot(oc, direction)
  //     c  = dot(oc, oc) - radius*radius
  // If the discriminant b*b - 4ac < 0 there is no hit -> return std::nullopt.
  // Otherwise take the nearest root t = (-b - sqrt(disc)) / (2a); if it is not
  // in (t_min, t_max), try the far root (-b + sqrt(disc)) / (2a); if that is
  // also out of range, return std::nullopt.
  // On a hit, fill a Hit: t, point = ray.at(t),
  //     normal = (point - center).normalized(),  material = material.
  std::optional<Hit> intersect(const Ray &ray, double t_min, double t_max) const override {
    return std::nullopt; // TODO
  }
};

TEST_CASE("Part 4: Sphere intersection") {
  Material m;
  Sphere s(Vec3(0, 0, -5), 1.0, m);
  Ray ray(Vec3(0, 0, 0), Vec3(0, 0, -1));
  auto hit = s.intersect(ray, 1e-4, std::numeric_limits<double>::infinity());
  REQUIRE(hit.has_value());
  CHECK(hit->t == doctest::Approx(4.0));
  CHECK(hit->normal.z == doctest::Approx(1.0));
  Ray miss(Vec3(0, 5, 0), Vec3(0, 0, -1));
  CHECK_FALSE(s.intersect(miss, 1e-4, std::numeric_limits<double>::infinity()).has_value());
}

// ============================================================================
// PART 5: Triangle::intersect  (Moeller-Trumbore algorithm)
// ============================================================================
class Triangle : public Object {
public:
  Vec3 v0, v1, v2;
  Triangle(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2, const Material &material)
      : Object(material), v0(v0), v1(v1), v2(v2) {}

  // TODO: Ray-triangle intersection using the Moeller-Trumbore algorithm.
  // Steps (return std::nullopt as soon as any test fails):
  //   edge1 = v1 - v0;  edge2 = v2 - v0;
  //   h = cross(ray.direction, edge2);   a = dot(edge1, h);
  //   if |a| < 1e-9: ray is parallel to the triangle -> miss.
  //   f = 1/a;   s = ray.origin - v0;   u = f * dot(s, h);
  //   if u < 0 or u > 1: miss.
  //   q = cross(s, edge1);   v = f * dot(ray.direction, q);
  //   if v < 0 or u + v > 1: miss.
  //   t = f * dot(edge2, q);
  //   if t not in (t_min, t_max): miss.
  //   normal = cross(edge1, edge2).normalized();
  //   if dot(normal, ray.direction) > 0: normal = -normal;  // face the ray
  //   Fill and return a Hit (t, ray.at(t), normal, material).
  std::optional<Hit> intersect(const Ray &ray, double t_min, double t_max) const override {
    return std::nullopt; // TODO
  }
};

TEST_CASE("Part 5: Triangle intersection") {
  Material m;
  Triangle tri(Vec3(-1, -1, -5), Vec3(1, -1, -5), Vec3(0, 1, -5), m);
  Ray ray(Vec3(0, 0, 0), Vec3(0, 0, -1));
  auto hit = tri.intersect(ray, 1e-4, std::numeric_limits<double>::infinity());
  REQUIRE(hit.has_value());
  CHECK(hit->t == doctest::Approx(5.0));
  CHECK(std::abs(hit->normal.z) == doctest::Approx(1.0));
  Ray miss(Vec3(3, 3, 0), Vec3(0, 0, -1));
  CHECK_FALSE(tri.intersect(miss, 1e-4, std::numeric_limits<double>::infinity()).has_value());
}

// ============================================================================
// PART 6: Camera - a pinhole camera that shoots primary rays through pixels.
// ============================================================================
class Camera {
public:
  // TODO: In the constructor body, build the camera basis and image-plane
  // vectors from the members initialised below (eye_ is already stored):
  //     aspect  = width / height
  //     theta   = vfov_deg * pi / 180        // use std::numbers::pi_v<double>
  //     half_h  = tan(theta / 2);   half_w = aspect * half_h
  //     forward_ = (look_at - eye).normalized()
  //     right_   = cross(forward_, up).normalized()
  //     true_up_ = cross(right_, forward_)
  //     horizontal_ = right_ * half_w;   vertical_ = true_up_ * half_h
  Camera(const Vec3 &eye, const Vec3 &look_at, const Vec3 &up, double vfov_deg,
         int image_width, int image_height)
      : eye_(eye) {
    // TODO
  }

  // TODO: Return the ray through pixel coordinate (s, t), where s and t are in
  // [0, 1] with (0, 0) at the top-left. Map them to [-1, 1] (flip t so row 0 is
  // the top):  u = 2s - 1,  v = 1 - 2t.  Then
  //     direction = forward_ + horizontal_ * u + vertical_ * v
  // and return Ray(eye_, direction).
  Ray ray_through(double s, double t) const {
    return Ray(eye_, Vec3(0, 0, -1)); // TODO
  }

private:
  Vec3 eye_, forward_, right_, true_up_, horizontal_, vertical_;
};

TEST_CASE("Part 6: Camera") {
  Camera cam(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0), 90.0, 100, 100);
  Ray center = cam.ray_through(0.5, 0.5);
  CHECK(center.direction.x == doctest::Approx(0).epsilon(0.01));
  CHECK(center.direction.y == doctest::Approx(0).epsilon(0.01));
  CHECK(center.direction.z == doctest::Approx(-1).epsilon(0.01));
}

// ============================================================================
// PART 7: Scene - the world: objects + lights, with the two ray queries the
// renderer needs.
// ============================================================================
class Scene {
public:
  std::vector<std::unique_ptr<Object>> objects;
  std::vector<Light> lights;
  Vec3 background = Vec3(0, 0, 0);
  Vec3 ambient = Vec3(0.1, 0.1, 0.1);

  // TODO: Return the CLOSEST hit among all objects, or std::nullopt if the ray
  // misses everything. Loop over objects; each time one reports a hit, keep it
  // as the best so far AND shrink t_max to that hit's t, so subsequent objects
  // only count if they are nearer.
  std::optional<Hit> closest_hit(const Ray &ray, double t_min, double t_max) const {
    return std::nullopt; // TODO
  }

  // TODO: Is any object between `point` and a light `light_distance` away in
  // direction `to_light`? Shoot a shadow ray from point (nudged a tiny bit
  // along to_light, e.g. point + to_light * 1e-4) and return whether
  // closest_hit finds anything with t in (1e-4, light_distance).
  bool in_shadow(const Vec3 &point, const Vec3 &to_light, double light_distance) const {
    return false; // TODO
  }
};

TEST_CASE("Part 7: Scene queries") {
  Scene scene;
  scene.objects.push_back(std::make_unique<Sphere>(Vec3(0, 0, -5), 1.0, Material{}));
  Ray ray(Vec3(0, 0, 0), Vec3(0, 0, -1));
  auto hit = scene.closest_hit(ray, 1e-4, std::numeric_limits<double>::infinity());
  REQUIRE(hit.has_value());
  CHECK(hit->t == doctest::Approx(4.0));
  // Blocker between a far point and a light: should be in shadow.
  CHECK(scene.in_shadow(Vec3(0, 0, 5), Vec3(0, 0, -1).normalized(), 100.0) == true);
  // Nothing between point and light: not shadowed.
  CHECK(scene.in_shadow(Vec3(0, 0, 5), Vec3(0, 1, 0).normalized(), 100.0) == false);
}

// --- GIVEN: Image + PNG encoder (do not modify) -----------------------------
// A simple RGB image (colours are Vec3 in [0,1]) with a self-contained PNG
// writer, so the project needs no external image library.
class Image {
public:
  Image(int width, int height)
      : width_(width), height_(height), pixels_(static_cast<size_t>(width) * height) {}
  int width() const { return width_; }
  int height() const { return height_; }
  void set(int x, int y, const Vec3 &color) { pixels_[index(x, y)] = color; }
  const Vec3 &at(int x, int y) const { return pixels_[index(x, y)]; }
  bool save_png(const std::string &filename) const;

private:
  size_t index(int x, int y) const { return static_cast<size_t>(y) * width_ + x; }
  int width_, height_;
  std::vector<Vec3> pixels_;
};

namespace png_detail {
inline void put_u32_be(std::vector<uint8_t> &out, uint32_t v) {
  out.push_back((v >> 24) & 0xFF);
  out.push_back((v >> 16) & 0xFF);
  out.push_back((v >> 8) & 0xFF);
  out.push_back((v >> 0) & 0xFF);
}
inline uint32_t crc32(const uint8_t *data, size_t len) {
  static uint32_t table[256];
  static bool ready = false;
  if (!ready) {
    for (uint32_t n = 0; n < 256; ++n) {
      uint32_t c = n;
      for (int k = 0; k < 8; ++k) c = (c & 1) ? (0xEDB88320u ^ (c >> 1)) : (c >> 1);
      table[n] = c;
    }
    ready = true;
  }
  uint32_t crc = 0xFFFFFFFFu;
  for (size_t i = 0; i < len; ++i) crc = table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
  return crc ^ 0xFFFFFFFFu;
}
inline uint32_t adler32(const uint8_t *data, size_t len) {
  const uint32_t MOD = 65521;
  uint32_t a = 1, b = 0;
  for (size_t i = 0; i < len; ++i) {
    a = (a + data[i]) % MOD;
    b = (b + a) % MOD;
  }
  return (b << 16) | a;
}
inline void write_chunk(std::vector<uint8_t> &out, const char type[4],
                        const std::vector<uint8_t> &data) {
  put_u32_be(out, static_cast<uint32_t>(data.size()));
  std::vector<uint8_t> td;
  td.insert(td.end(), type, type + 4);
  td.insert(td.end(), data.begin(), data.end());
  out.insert(out.end(), td.begin(), td.end());
  put_u32_be(out, crc32(td.data(), td.size()));
}
inline std::vector<uint8_t> zlib_store(const std::vector<uint8_t> &raw) {
  std::vector<uint8_t> out;
  out.push_back(0x78);
  out.push_back(0x01);
  const size_t MAX = 65535;
  for (size_t off = 0; off < raw.size() || off == 0; off += MAX) {
    size_t len = std::min(MAX, raw.size() - off);
    bool final = (off + len >= raw.size());
    out.push_back(final ? 1 : 0);
    out.push_back(len & 0xFF);
    out.push_back((len >> 8) & 0xFF);
    out.push_back(~len & 0xFF);
    out.push_back((~len >> 8) & 0xFF);
    out.insert(out.end(), raw.begin() + off, raw.begin() + off + len);
    if (len == 0) break;
  }
  put_u32_be(out, adler32(raw.data(), raw.size()));
  return out;
}
inline uint8_t to_byte(double c) {
  c = std::clamp(c, 0.0, 1.0);
  c = std::pow(c, 1.0 / 2.2); // gamma
  return static_cast<uint8_t>(c * 255.0 + 0.5);
}
} // namespace png_detail

inline bool Image::save_png(const std::string &filename) const {
  using namespace png_detail;
  std::vector<uint8_t> raw;
  raw.reserve(static_cast<size_t>(height_) * (1 + 3 * width_));
  for (int y = 0; y < height_; ++y) {
    raw.push_back(0);
    for (int x = 0; x < width_; ++x) {
      const Vec3 &c = pixels_[index(x, y)];
      raw.push_back(to_byte(c.x));
      raw.push_back(to_byte(c.y));
      raw.push_back(to_byte(c.z));
    }
  }
  std::vector<uint8_t> png;
  const uint8_t sig[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  png.insert(png.end(), sig, sig + 8);
  std::vector<uint8_t> ihdr;
  put_u32_be(ihdr, static_cast<uint32_t>(width_));
  put_u32_be(ihdr, static_cast<uint32_t>(height_));
  ihdr.push_back(8);
  ihdr.push_back(2);
  ihdr.push_back(0);
  ihdr.push_back(0);
  ihdr.push_back(0);
  write_chunk(png, "IHDR", ihdr);
  write_chunk(png, "IDAT", zlib_store(raw));
  write_chunk(png, "IEND", {});
  std::ofstream file(filename, std::ios::binary);
  if (!file) return false;
  file.write(reinterpret_cast<const char *>(png.data()),
             static_cast<std::streamsize>(png.size()));
  return static_cast<bool>(file);
}

// ============================================================================
// PART 8/9: Renderer - Phong local illumination (shade) + recursive mirror
// reflection (trace).
// ============================================================================
class Renderer {
public:
  explicit Renderer(const Scene &scene, int max_depth = 4)
      : scene_(scene), max_depth_(max_depth) {}

  // TODO (PART 8): Phong shading at a hit point.
  // Start with the ambient term:  color = scene_.ambient * material.diffuse.
  // view_dir = (-ray.direction).normalized().
  // For each light in scene_.lights:
  //     to_light = light.position - hit.point;  dist = to_light.length();
  //     light_dir = to_light / dist;
  //     if scene_.in_shadow(hit.point, light_dir, dist): skip this light.
  //     diffuse:  diff = max(0, dot(hit.normal, light_dir));
  //               color += material.diffuse * light.color * diff;
  //     specular (only when diff > 0):
  //               refl = reflect(-light_dir, hit.normal);
  //               spec = pow(max(0, dot(view_dir, refl)), material.shininess);
  //               color += material.specular * light.color * spec;
  // Return color.
  Vec3 shade(const Hit &hit, const Ray &ray) const {
    return {}; // TODO
  }

  // TODO (PART 9): Trace one ray and return its colour, with recursion for
  // mirror reflections.
  //   Base case: if depth > max_depth_, return Vec3(0,0,0).
  //   Find the nearest hit with scene_.closest_hit(ray, 1e-4, infinity).
  //   If nothing is hit, return scene_.background.
  //   Otherwise color = shade(hit, ray). Let r = hit.material.reflectivity.
  //   If r > 0: build the reflected ray from the hit point (nudged along the
  //   normal by 1e-4) in direction reflect(ray.direction, hit.normal), then
  //   RECURSE: color = color * (1 - r) + trace(reflected, depth + 1) * r.
  //   Return color.
  Vec3 trace(const Ray &ray, int depth) const {
    return scene_.background; // TODO
  }

private:
  const Scene &scene_;
  int max_depth_;
};

TEST_CASE("Part 8: Phong shading") {
  Scene scene;
  scene.ambient = Vec3(0, 0, 0);
  scene.lights.push_back(Light{Vec3(0, 0, 5), Vec3(1, 1, 1)});
  Renderer r(scene);
  Hit hit;
  hit.point = Vec3(0, 0, 0);
  hit.normal = Vec3(0, 0, 1);
  hit.material.diffuse = Vec3(0.4, 0.6, 0.8);
  hit.material.specular = Vec3(0, 0, 0);
  hit.material.shininess = 1.0;
  Ray ray(Vec3(0, 0, 10), Vec3(0, 0, -1));
  Vec3 c = r.shade(hit, ray);
  CHECK(c.x == doctest::Approx(0.4));
  CHECK(c.y == doctest::Approx(0.6));
  CHECK(c.z == doctest::Approx(0.8));
}

TEST_CASE("Part 9: trace hits and misses") {
  Scene scene;
  scene.background = Vec3(0.1, 0.2, 0.3);
  scene.ambient = Vec3(0, 0, 0);
  scene.lights.push_back(Light{Vec3(0, 0, 5), Vec3(1, 1, 1)});
  Material red;
  red.diffuse = Vec3(0.9, 0.1, 0.1);
  red.specular = Vec3(0, 0, 0);
  scene.objects.push_back(std::make_unique<Sphere>(Vec3(0, 0, -5), 1.0, red));
  Renderer r(scene);
  // Miss -> background.
  Vec3 bg = r.trace(Ray(Vec3(0, 10, 0), Vec3(0, 1, 0)), 0);
  CHECK(bg.x == doctest::Approx(0.1));
  CHECK(bg.z == doctest::Approx(0.3));
  // Hit -> red dominant.
  Vec3 hit = r.trace(Ray(Vec3(0, 0, 0), Vec3(0, 0, -1)), 0);
  CHECK(hit.x > hit.y);
  CHECK(hit.x > hit.z);
}

// --- GIVEN: scene file parser (do not modify) -------------------------------
// Reads the little scene-description language in scene.txt into a ParsedScene.
struct CameraConfig {
  Vec3 eye = Vec3(0, 0, 0);
  Vec3 look_at = Vec3(0, 0, -1);
  Vec3 up = Vec3(0, 1, 0);
  double fov = 60.0;
};
struct ParsedScene {
  Scene scene;
  CameraConfig camera;
  int width = 800;
  int height = 600;
};

namespace parse_detail {
inline double num(std::istringstream &in, const std::string &cmd, int ln) {
  double v;
  if (!(in >> v))
    throw std::runtime_error("line " + std::to_string(ln) + ": '" + cmd + "' expects more numbers");
  return v;
}
inline Vec3 vec(std::istringstream &in, const std::string &cmd, int ln) {
  double x = num(in, cmd, ln), y = num(in, cmd, ln), z = num(in, cmd, ln);
  return Vec3(x, y, z);
}
inline std::string word(std::istringstream &in, const std::string &cmd, int ln) {
  std::string w;
  if (!(in >> w))
    throw std::runtime_error("line " + std::to_string(ln) + ": '" + cmd + "' expects a name");
  return w;
}
} // namespace parse_detail

inline ParsedScene parse_scene(const std::string &filename) {
  using namespace parse_detail;
  std::ifstream file(filename);
  if (!file) throw std::runtime_error("could not open scene file: " + filename);
  ParsedScene result;
  std::map<std::string, Material> materials;
  std::string line;
  int ln = 0;
  while (std::getline(file, line)) {
    ++ln;
    if (auto hash = line.find('#'); hash != std::string::npos) line.erase(hash);
    std::istringstream in(line);
    std::string cmd;
    if (!(in >> cmd)) continue;
    if (cmd == "size") {
      result.width = static_cast<int>(num(in, cmd, ln));
      result.height = static_cast<int>(num(in, cmd, ln));
    } else if (cmd == "camera") {
      result.camera.eye = vec(in, cmd, ln);
      result.camera.look_at = vec(in, cmd, ln);
      result.camera.up = vec(in, cmd, ln);
      result.camera.fov = num(in, cmd, ln);
    } else if (cmd == "background") {
      result.scene.background = vec(in, cmd, ln);
    } else if (cmd == "ambient") {
      result.scene.ambient = vec(in, cmd, ln);
    } else if (cmd == "light") {
      Light light;
      light.position = vec(in, cmd, ln);
      light.color = vec(in, cmd, ln);
      result.scene.lights.push_back(light);
    } else if (cmd == "material") {
      std::string name = word(in, cmd, ln);
      Material m;
      m.diffuse = vec(in, cmd, ln);
      m.specular = vec(in, cmd, ln);
      m.shininess = num(in, cmd, ln);
      m.reflectivity = num(in, cmd, ln);
      materials[name] = m;
    } else if (cmd == "sphere") {
      Vec3 center = vec(in, cmd, ln);
      double radius = num(in, cmd, ln);
      std::string name = word(in, cmd, ln);
      auto it = materials.find(name);
      if (it == materials.end())
        throw std::runtime_error("line " + std::to_string(ln) + ": unknown material '" + name + "'");
      result.scene.objects.push_back(std::make_unique<Sphere>(center, radius, it->second));
    } else if (cmd == "triangle") {
      Vec3 a = vec(in, cmd, ln), b = vec(in, cmd, ln), c = vec(in, cmd, ln);
      std::string name = word(in, cmd, ln);
      auto it = materials.find(name);
      if (it == materials.end())
        throw std::runtime_error("line " + std::to_string(ln) + ": unknown material '" + name + "'");
      result.scene.objects.push_back(std::make_unique<Triangle>(a, b, c, it->second));
    } else {
      throw std::runtime_error("line " + std::to_string(ln) + ": unknown command '" + cmd + "'");
    }
  }
  return result;
}

// ============================================================================
// PART 10: Render the scene to a PNG. This test drives everything above; once
// all earlier parts work, it produces "out.png" - open it to see your render!
// ============================================================================
TEST_CASE("Part 10: render scene.txt to out.png") {
  // NOTE: run from the cpplings repo root so this relative path resolves.
  ParsedScene parsed = parse_scene("exercises/05_capstone/scenes/test.txt");
  Camera camera(parsed.camera.eye, parsed.camera.look_at, parsed.camera.up,
                parsed.camera.fov, parsed.width, parsed.height);
  Renderer renderer(parsed.scene);
  Image image(parsed.width, parsed.height);
  for (int y = 0; y < parsed.height; ++y)
    for (int x = 0; x < parsed.width; ++x) {
      double s = (x + 0.5) / parsed.width;
      double t = (y + 0.5) / parsed.height;
      image.set(x, y, renderer.trace(camera.ray_through(s, t), 0));
    }
  CHECK(image.save_png("out.png") == true);
  // Corner ray misses the centred sphere -> background sky.
  const Vec3 &corner = image.at(0, 0);
  CHECK(corner.x == doctest::Approx(parsed.scene.background.x));
  CHECK(corner.z == doctest::Approx(parsed.scene.background.z));
  // Center ray hits the red sphere -> red channel dominates.
  const Vec3 &mid = image.at(parsed.width / 2, parsed.height / 2);
  CHECK(mid.x > mid.y);
  CHECK(mid.x > mid.z);
}

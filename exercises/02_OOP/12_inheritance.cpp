#include <doctest/doctest.h>

// TODO: Define a struct `Shape` with:
//   - a const char* member `name`
//   - a constructor taking a name
//
// TODO: Define a struct `Circle` that inherits from Shape with:
//   - a double member `radius`
//   - a constructor taking a radius (pass "circle" to the Shape constructor)
//   - a function `area()` that returns 3.14159265 * radius * radius

TEST_CASE("inheritance") {
  Circle c{5.0};
  CHECK(c.area() == doctest::Approx(78.5398).epsilon(0.01));
  CHECK(c.name == doctest::String("circle"));
}

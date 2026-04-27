#include <doctest/doctest.h>

//
// TODO: Define a struct `Vec2` with float members `x` and `y`.
// Implement:
//   - operator+ that adds two Vec2
//   - operator== that compares two Vec2

struct Vec2 {
  float x, y;
  // TODO: implement operator+ and operator==
};

TEST_CASE("operator plus and equals") {
  Vec2 a{1.0f, 2.0f};
  Vec2 b{3.0f, 4.0f};
  Vec2 c = a + b;
  CHECK(c.x == doctest::Approx(4.0f));
  CHECK(c.y == doctest::Approx(6.0f));
  CHECK((c == Vec2{4.0f, 6.0f}));
  CHECK(!(c == a));
}

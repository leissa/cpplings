#include <doctest/doctest.h>

// TODO: Define a struct `Rect` with:
//   - int members `width` and `height`
//   - a constructor that takes width and height
//   - a function `area()` that returns width * height

// TODO: define Rect here

TEST_CASE("constructor") {
  Rect r{3, 7};
  CHECK(r.area() == 21);
  Rect square{5, 5};
  CHECK(square.area() == 25);
}

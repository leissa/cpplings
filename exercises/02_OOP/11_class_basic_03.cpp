#include <doctest/doctest.h>

// TODO: Define a struct `Pair` with:
//   - two int members `x` and `y` (default initialized to 0)
//   - a constructor taking two ints
//   - a default constructor (use = default)
// Both constructors must work.

// TODO: define Pair here

TEST_CASE("default constructor") {
  Pair p1;
  CHECK(p1.x == 0);
  CHECK(p1.y == 0);

  Pair p2{3, 7};
  CHECK(p2.x == 3);
  CHECK(p2.y == 7);
}

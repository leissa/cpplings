#include <doctest/doctest.h>

// TODO: Define a struct called `Point` with two int members: x and y.
// Then implement a function that returns a Point with x=3, y=7.

struct Point; // TODO: replace this forward declaration with a full definition

Point make_point() {
  return {}; // TODO: return a Point with x=3, y=7
}

TEST_CASE("struct basic") {
  Point p = make_point();
  CHECK(p.x == 3);
  CHECK(p.y == 7);
}

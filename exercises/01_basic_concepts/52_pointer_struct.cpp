#include <doctest/doctest.h>

// TODO: Implement the function using the arrow operator.

struct Point {
  int x;
  int y;
};

int sum_point(Point *p) { return 0; }

TEST_CASE("struct pointer access") {
  Point pt = {10, 32};
  CHECK(sum_point(&pt) == 42);
}

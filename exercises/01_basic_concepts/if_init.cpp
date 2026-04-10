#include <doctest/doctest.h>

// TODO: Use an if-with-initializer to compute x*x, and return it
// only if it is less than 100. Otherwise return -1.

int square_if_small(int x) { return 0; }

TEST_CASE("if initializer") {
  CHECK(square_if_small(5) == 25);
  CHECK(square_if_small(9) == 81);
  CHECK(square_if_small(10) == -1);
  CHECK(square_if_small(15) == -1);
}

#include <doctest/doctest.h>

// TODO: Define a lambda called `square` that takes an int
// and returns its square.

auto square = ? ;

TEST_CASE("lambda basic") {
  CHECK(square(5) == 25);
  CHECK(square(-3) == 9);
  CHECK(square(0) == 0);
}

#include <doctest/doctest.h>

// TODO: Implement make_power that returns a lambda which raises its argument to
// the power of 'n'

auto make_power(int n) { return ? ; }

TEST_CASE("lambda return") {
  auto square = make_adder(2);
  auto cube = make_adder(3);
  CHECK(square(10) == 100);
  CHECK(square(0) == 0);
  CHECK(cube(4) == 64);
}

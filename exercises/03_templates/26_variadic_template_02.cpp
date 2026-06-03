#include <doctest/doctest.h>

// TODO: Implement a variadic function template 'sum' that:
//   - base case: takes one argument T a, returns a
//   - recursive case: takes T a and TArgs... rest, returns a + sum(rest...)

// TODO: define sum here

TEST_CASE("variadic sum") {
  CHECK(sum(1) == 1);
  CHECK(sum(1, 2, 3) == 6);
  CHECK(sum(1, 2, 3, 4, 5) == 15);
  CHECK(sum(1.5, 2.5) == doctest::Approx(4.0));
}

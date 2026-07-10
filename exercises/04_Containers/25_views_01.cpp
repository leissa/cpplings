#include <doctest/doctest.h>
#include <numeric>
#include <ranges>
#include <vector>

// TODO: Implement sum_of_cubes(n) that returns the sum of the cubes
// of integers from 1 to n (inclusive) using:
//   std::views::iota
//   std::views::transform(...)
//   fold

int sum_of_cubes(int n) {
  return 0; // TODO
}

TEST_CASE("iota and transform") {
  CHECK(sum_of_cubes(1) == 1);
  CHECK(sum_of_cubes(3) == 36);
  CHECK(sum_of_cubes(5) == 225);
}

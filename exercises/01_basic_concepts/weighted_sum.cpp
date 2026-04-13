#include <doctest/doctest.h>

// TODO: Use a range-for with initializer to compute a weighted sum.
// The weight starts at 1 and increments by 1 for each element.
// weighted_sum({10, 20, 30}) = 1*10 + 2*20 + 3*30 = 10 + 40 + 90 = 140

int weighted_sum() {
  int sum = 0;
  return sum;
}

TEST_CASE("range for with initializer") { CHECK(weighted_sum() == 140); }

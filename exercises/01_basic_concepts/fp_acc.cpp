#include <cmath>
#include <doctest/doctest.h>

// TODO: Fix this function so it returns an accurate sum of n * increment
// even for large n.
//
float accurate_sum(int n, float increment) {
  float sum = 0.0f;
  for (int i = 0; i < n; i++) {
    sum += increment;
  }
  return sum;
}

TEST_CASE("accumulation error") {
  // Naively adding 1.0f twenty million times does NOT give 20000000.0f
  // due to precision loss at large values.
  float result = accurate_sum(20000000, 1.0f);
  CHECK(result == doctest::Approx(20000000.0f).epsilon(1e-6));
}

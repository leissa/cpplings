#include <cmath>
#include <doctest/doctest.h>

//
// TODO: Compute the smaller root (x2) of x^2 + 5000x + 0.25 = 0 accurately.
// The naive formula gives 0 due to catastrophic cancellation.

// Hint:Use the alternative formula: x2 = c / ((-b - sqrt(b^2 - 4ac)) / 2)
// or equivalently: 2c / (-b - sqrt(b^2 - 4ac))
double quadratic_small_root(double a, double b, double c) {
  return (-b + std::sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
}

TEST_CASE("catastrophic cancellation") {
  double root = quadratic_small_root(1.0, 5000.0, 0.25);
  CHECK(root == doctest::Approx(-0.00005).epsilon(0.01));
}

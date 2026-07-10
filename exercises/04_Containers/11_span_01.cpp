#include <algorithm>
#include <doctest/doctest.h>
#include <numeric>
#include <span>

// TODO: Implement scale(data, factor)
//   Takes a std::span<double> and multiplies every element by factor.
//   Modifies the data in-place — no return value needed.

void scale(std::span<double> data, double factor) {
  // TODO
}

// TODO: Implement dot_product(a, b)
//   Takes two std::span<const double> and returns their dot product.
//   Assume a.size() == b.size().

double dot_product(std::span<const double> a, std::span<const double> b) {
  return 0.0; // TODO
}

TEST_CASE("span scale in-place") {
  std::vector<double> v = {1.0, 2.0, 3.0, 4.0};
  scale(v, 2.0);
  CHECK(v == std::vector<double>{2.0, 4.0, 6.0, 8.0});

  double arr[] = {1.0, 2.0, 3.0};
  scale(arr, 0.5);
  CHECK(arr[0] == doctest::Approx(0.5));
  CHECK(arr[1] == doctest::Approx(1.0));
  CHECK(arr[2] == doctest::Approx(1.5));
}

TEST_CASE("span dot product") {
  std::vector<double> a = {1.0, 2.0, 3.0};
  std::vector<double> b = {4.0, 5.0, 6.0};
  CHECK(dot_product(a, b) == doctest::Approx(32.0));
}

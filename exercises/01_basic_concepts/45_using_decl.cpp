#include <doctest/doctest.h>

namespace geometry {
double area_of_square(double side) { return side * side; }
double area_of_circle(double radius) { return 3.14159265 * radius * radius; }
} // namespace geometry

// TODO: Use a using-declaration to bring ONLY area_of_square into scope.
// Do NOT use `using namespace`.

double compute_square_area(double side) {
  return area_of_square(side); // make this work without the namespace prefix
}

TEST_CASE("using declaration") {
  CHECK(compute_square_area(4.0) == doctest::Approx(16.0));
}

#include <doctest/doctest.h>

// TODO: Define a generic lambda `maximum` that takes two arguments
// of any type and returns the larger one.

auto maximum = [](auto a, auto b) { return a; };

TEST_CASE("generic lambda") {
  CHECK(maximum(3, 7) == 7);
  CHECK(maximum(10, 2) == 10);
  CHECK(maximum(3.14, 2.72) == doctest::Approx(3.14));
  CHECK(maximum('a', 'z') == 'z');
}

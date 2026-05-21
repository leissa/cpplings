#include <doctest/doctest.h>

// TODO: Implement a function template 'scale' that takes a value
// of type T and a factor of type F, and returns T * F.
// Assume both T and F support operatoin *

// TODO: define scale here

TEST_CASE("two type parameters") {
  CHECK(scale(3, 2) == 6);
  CHECK(scale(3, 2.5) == doctest::Approx(7.5));
  CHECK(scale(1.5f, 4) == doctest::Approx(6.0f));
}

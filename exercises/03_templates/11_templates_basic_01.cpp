#include <doctest/doctest.h>

// TODO: Implement a function template 'square' that takes a value of
// any type T and returns T * T.
// Assume that T supports operation *

// TODO: define square here

TEST_CASE("function template basic") {
  CHECK(square(3) == 9);
  CHECK(square(4.0) == doctest::Approx(16.0));
  CHECK(square(2.0f) == doctest::Approx(4.0f));
  CHECK(square(-5) == 25);
  CHECK(square(-2.5) == 6.25);
}

#include <doctest/doctest.h>

// TODO: Implement a function template 'is_zero' that returns
// (x == T{}) for a generic type T.
// Then provide a full specialization for float that returns true for absolute
// values less than 1e-6f instead of exact comparison.

// TODO: define is_zero and its float specialization here

TEST_CASE("template specialization") {
  CHECK(is_zero(0) == true);
  CHECK(is_zero(1) == false);
  CHECK(is_zero(0.0) == true);
  CHECK(is_zero(0.1) == false);

  CHECK(is_zero(0.0f) == true);
  CHECK(is_zero(1e-7f) == true); // nearly zero, specialization handles this
  CHECK(is_zero(0.1f) == false);
}

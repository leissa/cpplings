#include <doctest/doctest.h>

// TODO: Implement a constexpr function factorial and verify compile-time
// evaluation using static_assert.

TEST_CASE("constexpr function") {
  static_assert(factorial(5) == 120);

  CHECK(factorial(5) == 120);
  CHECK(factorial(0) == 1);
  CHECK(factorial(1) == 1);
}

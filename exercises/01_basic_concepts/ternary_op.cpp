#include <doctest/doctest.h>

// TODO: Implement a function that returns the absolute value of an int
// using ONLY the ternary operator (no if statements, no std::abs).

int my_abs(int x) { return 0; }

TEST_CASE("ternary operator") {
  CHECK(my_abs(5) == 5);
  CHECK(my_abs(-3) == 3);
  CHECK(my_abs(0) == 0);
}

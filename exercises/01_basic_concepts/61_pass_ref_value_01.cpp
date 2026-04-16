#include <doctest/doctest.h>

// TODO: Fix this function. It's supposed to double the original value.
// Change the parameter passing method so the original is modified.

void double_it(int x) { x = x * 2; }

TEST_CASE("pass by value vs reference") {
  int val = 21;
  double_it(val);
  CHECK(val == 42);
}

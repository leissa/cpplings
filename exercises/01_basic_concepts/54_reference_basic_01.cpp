#include <doctest/doctest.h>

// TODO: Write a function "increment" that uses a reference to increment the
// original variable.

TEST_CASE("reference basics") {
  int x = 41;
  increment(x);
  CHECK(x == 42);
}

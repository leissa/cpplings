#include <doctest/doctest.h>

// TODO: Fix the function to return the value that ptr points to, plus 10.

int add_ten_via_pointer(int *ptr) { return 0; }

TEST_CASE("pointer basics") {
  int x = 32;
  CHECK(add_ten_via_pointer(&x) == 42);
}

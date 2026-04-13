#include <doctest/doctest.h>

// TODO: Fix the function to swap two integers using references.

void swap_refs(int &a, int &b) {}

TEST_CASE("reference swap") {
  int x = 10, y = 20;
  swap_refs(x, y);
  CHECK(x == 20);
  CHECK(y == 10);
}

#include <doctest/doctest.h>

// TODO: Implement a function that sets the value pointed to by `out`
// to the sum of `a` and `b`.

void sum_into(int a, int b, int *out) {}

TEST_CASE("pass by pointer") {
  int result = 0;
  sum_into(17, 25, &result);
  CHECK(result == 42);

#include <doctest/doctest.h>

// TODO: Use a range-based for loop with structured bindings to
// compute the sum of all x*y products from the array of pairs.

struct Pair {
  int x;
  int y;
};

int sum_products() {
  Pair pairs[] = {{2, 3}, {4, 5}, {1, 10}};
  int sum = 0;
  return sum;
}

TEST_CASE("range for struct binding") {
  // 2*3 + 4*5 + 1*10 = 6 + 20 + 10 = 36
  CHECK(sum_products() == 36);
}

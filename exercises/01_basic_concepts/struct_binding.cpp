#include <doctest/doctest.h>

// TODO: Use structured bindings (auto [a, b] = ...) to extract
// the members of the struct and return their sum.

struct Pair {
  int first;
  int second;
};

int sum_pair(Pair p) { return 0; }

TEST_CASE("struct binding") {
  CHECK(sum_pair({10, 20}) == 30);
  CHECK(sum_pair({-5, 5}) == 0);
}

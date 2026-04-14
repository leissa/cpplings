#include <doctest/doctest.h>

// TODO: Fix the function signature to accept a const reference
// to an array wrapper, preventing both copying and modification.

struct BigData {
  int values[1000];
  int size;
};

int first_element(BigData data) { return data.values[0]; }

TEST_CASE("const ref param") {
  BigData d{};
  d.values[0] = 42;
  d.size = 1000;
  CHECK(first_element(d) == 42);
}

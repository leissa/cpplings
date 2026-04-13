#include <doctest/doctest.h>

// TODO: Find a float value `big` such that (big + 1.0f) == big
// Hint: Think about when 1.0 is smaller than the ULP of big.
float find_big() { return 0.0f; }

TEST_CASE("precision loss") {
  float big = find_big();
  CHECK(big > 0.0f);
  CHECK(big + 1.0f == big);
}

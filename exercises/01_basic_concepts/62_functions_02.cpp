#include <doctest/doctest.h>

// TODO: Add default parameters so that:
//   - power defaults to 2 (square)
//   - offset defaults to 0

int transform(int value, int power, int offset) {
  int result = 1;
  for (int i = 0; i < power; i++)
    result *= value;
  return result + offset;
}

TEST_CASE("default parameters") {
  CHECK(transform(3, 2, 0) == 9);
  CHECK(transform(3) == 9);
  CHECK(transform(3, 3) == 27);
  CHECK(transform(3, 2, 10) == 19);
}

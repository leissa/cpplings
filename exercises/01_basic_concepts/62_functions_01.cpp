#include <doctest/doctest.h>

// TODO: Implement three overloads of `describe`:
//   - describe(int)    -> returns "int"
//   - describe(double) -> returns "double"
//   - describe(char)   -> returns "char"

TEST_CASE("function overloading") {
  CHECK(describe(42) == doctest::String("int"));
  CHECK(describe(3.14) == doctest::String("double"));
  CHECK(describe('x') == doctest::String("char"));
}

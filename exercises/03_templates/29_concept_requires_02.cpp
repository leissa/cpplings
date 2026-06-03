#include <doctest/doctest.h>

// TODO: Define a concept 'Addable' that is satisfied when:
//   - two values of type T can be added together (a + b is valid)
//   - the result is convertible to T
//   Use a requires expression with a type requirement.
//
// Then constrain 'sum_pair' to only accept Addable types.

TEST_CASE("requires expression") {
  CHECK(sum_pair(3, 4) == 7);
  CHECK(sum_pair(1.5, 2.5) == doctest::Approx(4.0));

  struct NoAdd {}; // does not support operator+

  static_assert(Addable<int>);
  static_assert(Addable<double>);
  static_assert(!Addable<NoAdd>);
}

#include <doctest/doctest.h>
#include <type_traits>

// TODO: Define the following type aliases using decltype:
//   - 'IntPlusDouble'  the type of (int{} + double{})
//   - 'FloatPlusInt'   the type of (float{} + int{})
//
// TODO: Implement a function template 'add_mixed(T a, R b)'
// that returns a + b. Use decltype(a + b) as the trailing return type.

// TODO: define aliases and add_mixed here

TEST_CASE("decltype aliases") {
  static_assert(std::is_same_v<IntPlusDouble, double>);
  static_assert(std::is_same_v<FloatPlusInt, float>);
}

TEST_CASE("decltype trailing return type") {
  auto r1 = add_mixed(1, 2.5);
  static_assert(std::is_same_v<decltype(r1), double>);
  CHECK(r1 == doctest::Approx(3.5));

  auto r2 = add_mixed(1.5f, 2);
  static_assert(std::is_same_v<decltype(r2), float>);
  CHECK(r2 == doctest::Approx(3.5f));
}

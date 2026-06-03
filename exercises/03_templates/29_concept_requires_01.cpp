#include <doctest/doctest.h>
#include <type_traits>

// TODO: Implement 'fp_divide' that:
//   - takes two values of the same type T
//   - uses a requires clause to ensure T is floating point
//   - returns a / b

TEST_CASE("requires clause") {
  CHECK(fp_divide(10.0, 4.0) == doctest::Approx(2.5));
  CHECK(fp_divide(7.0f, 2.0f) == doctest::Approx(3.5f));

  static_assert(std::is_floating_point_v<float>);
  static_assert(std::is_floating_point_v<double>);
  static_assert(!std::is_floating_point_v<int>);
  static_assert(!std::is_floating_point_v<bool>);
}

#include <doctest/doctest.h>
#include <type_traits>

// TODO: Implement 'integral_average' that:
//   - takes two values of type T
//   - uses static_assert with std::is_integral_v<T> to reject
//     non-integral types at compile time
//   - returns average of the 2 value
//
// TODO: define integral_average here

TEST_CASE("type traits with static assert") {
  CHECK(integral_average(4, 8) == 6);
  CHECK(integral_average(3, 3) == 3);
  CHECK(integral_average(0, 100) == 50);
  CHECK(integral_average(3, 4) == 3);
  CHECK(integral_average(1, 2) == 1);
}

#include <doctest/doctest.h>
#include <type_traits>

// TODO: Define a generic class template 'IsSame<T, R>' with:
//   - a static constexpr bool 'value = false'
//
// Then provide a partial specialization for the case where T == R:
//   - static constexpr bool 'value = true'

// TODO: define IsSame here

TEST_CASE("partial specialization is_same") {
  static_assert(IsSame<int, int>::value == true);
  static_assert(IsSame<int, float>::value == false);
  static_assert(IsSame<double, double>::value == true);
  static_assert(IsSame<int, unsigned>::value == false);
  CHECK(true);
}

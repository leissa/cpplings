#include <doctest/doctest.h>

// TODO: Define a class template 'Power<int Base, int E>' with:
//   - a static constexpr int 'value'
//   - generic case: value = Base * Power<Base, E-1>::value
//   - partial specialization for E == 0: value = 1

// TODO: define Power here

TEST_CASE("template metaprogramming power") {
  static_assert(Power<2, 0>::value == 1);
  static_assert(Power<2, 1>::value == 2);
  static_assert(Power<2, 8>::value == 256);
  static_assert(Power<3, 4>::value == 81);
  static_assert(Power<5, 3>::value == 125);
  CHECK(true);
}

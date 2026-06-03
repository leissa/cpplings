#include <doctest/doctest.h>

// TODO: Define a class template 'Factorial<N>' with:
//   - a static constexpr int 'value'
//   - generic case: value = N * Factorial<N-1>::value
//   - full specialization for N == 0: value = 1

// TODO: define Factorial here

TEST_CASE("template metaprogramming factorial") {
  static_assert(Factorial<0>::value == 1);
  static_assert(Factorial<1>::value == 1);
  static_assert(Factorial<5>::value == 120);
  static_assert(Factorial<6>::value == 720);
  CHECK(Factorial<10>::value == 3628800);
}

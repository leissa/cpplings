#include <doctest/doctest.h>
#include <type_traits>

// TODO: Define a concept 'Numeric' that is satisfied when T is
// an arithmetic type.
//
// Then implement a function template 'twice' constrained by Numeric
// that returns x * 2.
//
TEST_CASE("concept basic") {
  CHECK(twice(3) == 6);
  CHECK(twice(2.5) == doctest::Approx(5.0));
  CHECK(twice(2.5f) == doctest::Approx(5.0f));

  static_assert(Numeric<int>);
  static_assert(Numeric<float>);
  static_assert(Numeric<double>);
  static_assert(!Numeric<std::string>);
  static_assert(!Numeric<bool *>);
}

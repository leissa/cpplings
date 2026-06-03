#include <doctest/doctest.h>

// TODO: Define a generic class template 'Formatter<T>' with:
//   - a static function 'format(T v)' that returns v as-is (type T)
//
// Then provide a full specialization for bool that returns
// "true" or "false" as a const char*.

// TODO: define Formatter here

TEST_CASE("class template full specialization") {
  CHECK(Formatter<int>::format(42) == 42);
  CHECK(Formatter<double>::format(3.14) == doctest::Approx(3.14));
  CHECK(std::string(Formatter<bool>::format(true)) == "true");
  CHECK(std::string(Formatter<bool>::format(false)) == "false");
}

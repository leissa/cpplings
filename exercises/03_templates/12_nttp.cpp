#include <doctest/doctest.h>

// TODO: Implement a function template that takes a
// compile-time int N as a non-type template parameter and a runtime
// value x of type T, and returns x + N.
// Call it as: add_constant<5>(3).

// TODO: define add_constant here

TEST_CASE("non-type template parameter") {
  CHECK(add_constant<5>(3) == 8);
  CHECK(add_constant<10>(1.5) == doctest::Approx(11.5));
  CHECK(add_constant<0>(99) == 99);
  CHECK(add_constant<-3>(10) == 7);
}

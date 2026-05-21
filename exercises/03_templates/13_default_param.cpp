#include <doctest/doctest.h>

// TODO: Implement a function template 'clamp_to' that:
//   - takes a non-type template parameter int MAX defaulting to 100
//   - takes a value x of type T
//   - returns x if x <= MAX, otherwise returns static_cast<T>(MAX)

// TODO: define clamp_to here

TEST_CASE("template default parameter") {
  CHECK(clamp_to(50) == 50);
  CHECK(clamp_to(150) == 100);
  CHECK(clamp_to<50>(30) == 30);
  CHECK(clamp_to<50>(80) == 50);
}

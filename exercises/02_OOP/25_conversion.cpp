#include <doctest/doctest.h>

// TODO: Define a struct `Percentage` with a double member `value`.
// Implement an EXPLICIT conversion operator to double.
// Implement an IMPLICIT conversion operator to bool
// that returns true if value > 0.

struct Percentage {
  double value;
  // TODO: implement explicit operator double and operator bool
};

TEST_CASE("conversion operator") {
  Percentage p{75.0};
  CHECK(static_cast<double>(p) == doctest::Approx(75.0));
  CHECK(p); // implicit bool conversion

  Percentage zero{0.0};
  CHECK(!zero);
}

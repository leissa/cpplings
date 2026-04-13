#include <cmath>
#include <doctest/doctest.h>
#include <limits>

// TODO: Implement a function that returns true only if the value
// is a valid, finite, non-NaN floating point number.
// Use the appropriate function from <cmath>.
bool is_usable(double value) {
  return true; // TODO: fix this
}

TEST_CASE("is usable") {
  CHECK(is_usable(42.0));
  CHECK(is_usable(-3.14));
  CHECK(is_usable(0.0));
  CHECK_FALSE(is_usable(std::numeric_limits<double>::infinity()));
  CHECK_FALSE(is_usable(-std::numeric_limits<double>::infinity()));
  CHECK_FALSE(is_usable(std::numeric_limits<double>::quiet_NaN()));
}

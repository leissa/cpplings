#include <doctest/doctest.h>
#include <limits>

// TODO: Return the most negative float value (i.e., the float closest to
// -infinity). Hint: it's NOT std::numeric_limits<float>::min()
float most_negative_float() { return 0.0f; }

TEST_CASE("lowest vs min for float") {
  CHECK(most_negative_float() < 0.0f);
  CHECK(most_negative_float() == std::numeric_limits<float>::lowest());
  CHECK(most_negative_float() != std::numeric_limits<float>::min());
}

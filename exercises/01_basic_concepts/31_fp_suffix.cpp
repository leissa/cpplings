#include <doctest/doctest.h>

// TODO: Return the value 3.14 as a float.
// Use the appropriate suffix literal.
auto pi_float() { return 3.14; }

TEST_CASE("float suffix") {
  CHECK(std::is_same_v<decltype(pi_float()), float>);
}

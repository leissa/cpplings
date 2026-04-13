#include <doctest/doctest.h>
#include <limits>
// TODO: return the maximum value an int can hold.
// Do not hardcode the number.
int max_int() { return 0; }
TEST_CASE("max int") { CHECK(max_int() == std::numeric_limits<int>::max()); }

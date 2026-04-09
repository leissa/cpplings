#include <doctest/doctest.h>
// TODO: fix the return type using auto and trailing return type syntax.
? add(int a, int b) { return a + b; }
TEST_CASE("auto return") { CHECK(add(2, 3) == 5); }

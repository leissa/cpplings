#include <doctest/doctest.h>
// TODO: fix the function to return the correct average as a double.
double average(int a, int b) { return (a + b) / 2; }
TEST_CASE("average") { CHECK(average(3, 4) == 3.5); }

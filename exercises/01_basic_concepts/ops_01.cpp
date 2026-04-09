#include <doctest/doctest.h>

// TODO: fix the function to return the value of i AFTER incrementing.
int prefix_inc(int i) { return i++; }

TEST_CASE("prefix") { CHECK(prefix_inc(4) == 5); }

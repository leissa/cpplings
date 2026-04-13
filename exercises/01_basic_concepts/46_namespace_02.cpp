#include <doctest/doctest.h>

// TODO: Define a nested namespace `company::project::util` containing
// a function `int add(int a, int b)` that returns a + b.
// Use the C++17 compact syntax.

TEST_CASE("nested namespace") { CHECK(company::project::util::add(3, 4) == 7); }

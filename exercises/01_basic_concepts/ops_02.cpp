#include <doctest/doctest.h>

// TODO: add parentheses to make the expression evaluate to 10.
int result() { return 2 + 3 * 3 - 5; }

TEST_CASE("precedence") { CHECK(result() == 10); }

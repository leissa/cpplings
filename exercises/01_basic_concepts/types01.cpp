#include <doctest/doctest.h>

// TODO: which type has exactly 8 bytes on all platforms?
// Fix the return type of this function.
? eight_byte_type() { return 0; }

TEST_CASE("eight bytes") { CHECK(sizeof(eight_byte_type()) == 8); }

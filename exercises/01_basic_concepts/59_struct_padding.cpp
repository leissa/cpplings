#include <doctest/doctest.h>

//
// TODO: Define two structs, Padded and Compact, each with the same
// three members: a char, an int, and a char.
// Order the members in Padded so that sizeof(Padded) == 12.
// Order the members in Compact so that sizeof(Compact) == 8.
//

struct Padded {};

struct Compact {};

TEST_CASE("sizeof struct padding") {
  CHECK(sizeof(Padded) == 12);
  CHECK(sizeof(Compact) == 8);
  CHECK(sizeof(Compact) < sizeof(Padded));
}

#include <doctest/doctest.h>

// TODO: Define a class `Secret` with:
//   - a PRIVATE int member `code`
//   - a constructor taking an int
//   - a friend function `crack(const Secret& s)` that returns the code

// TODO: define Secret and crack here

TEST_CASE("friend function") {
  Secret s{42};
  CHECK(crack(s) == 42);
}

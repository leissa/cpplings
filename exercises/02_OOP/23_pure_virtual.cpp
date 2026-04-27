#include <doctest/doctest.h>

// TODO: Define an abstract class `Printable` with a pure virtual
// function `to_string()` returning a const char*.
// Then define two concrete classes that implement it.

// TODO: define Printable, Good, and Bad here

const char *describe(Printable &p) { return p.to_string(); }

TEST_CASE("pure virtual") {
  Good g;
  Bad b;
  CHECK(describe(g) == doctest::String("good"));
  CHECK(describe(b) == doctest::String("bad"));
}

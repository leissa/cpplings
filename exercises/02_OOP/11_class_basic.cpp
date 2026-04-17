#include <doctest/doctest.h>

// TODO: Define a struct `Counter` with:
//   - an int data member `count` (default initialized to 0)
//   - a function member `increment()` that adds 1 to count
//   - a function member `get()` that returns count

class Counter;

TEST_CASE("basic class") {
  Counter c;
  CHECK(c.get() == 0);
  c.increment();
  c.increment();
  c.increment();
  CHECK(c.get() == 3);
}

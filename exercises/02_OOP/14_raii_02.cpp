#include <doctest/doctest.h>

// TODO: Define a class `ScopedCounter` with:
//   - a private int& member that refers to an external counter
//   - a constructor that takes an int& and increments it
//   - a destructor that decrements it

// TODO: define ScopedCounter here

TEST_CASE("raii scope release") {
  int active = 0;
  CHECK(active == 0);

  {
    ScopedCounter a(active);
    CHECK(active == 1);

    {
      ScopedCounter b(active);
      CHECK(active == 2);
    }

    CHECK(active == 1);
  }

  CHECK(active == 0);
}

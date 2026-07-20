#include <doctest/doctest.h>

// TODO: Define a base class `Base` with:
//   - A constructor that takes an int* and increments the value it points to.
//   - A destructor that decrements the value it points to.
//   - A virtual destructor (required for polymorphic deletion).
//
// TODO: Define a derived class `Derived` that inherits from `Base`:
//   - Has a constructor taking two int* parameters: one for Base, one for
//   extra.
//   - Increments the second counter in the constructor.
//   - Has a destructor that decrements the second counter.
//   - Must override the destructor.
//
// Note: The destructor in Base must be virtual so that both destructors run
//       when deleting a Derived object through a Base pointer.
//
struct Base {
  int *log;
  // constructor
  // destructor
};

struct Derived : Base {
  int *extra;
  // constructor
  // destructor
};

TEST_CASE("virtual destructor") {
  int base_count = 0;
  int derived_count = 0;

  Base *p = new Derived(&base_count, &derived_count);
  CHECK(base_count == 1);
  CHECK(derived_count == 1);

  delete p;
  CHECK(derived_count == 0); // derived destructor must have run
  CHECK(base_count == 0);    // base destructor must have run
}

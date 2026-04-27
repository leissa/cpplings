#include <doctest/doctest.h>

// TODO: Make the Base destructor virtual so both destructors run.

struct Base {
  int *log;
  Base(int *l) : log(l) { *log += 1; }
  ~Base() { *log -= 1; }
};

struct Derived : Base {
  int *extra;
  Derived(int *l, int *e) : Base(l), extra(e) { *extra += 1; }
  ~Derived() { *extra -= 1; }
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

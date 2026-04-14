#include <doctest/doctest.h>

// TODO: Fix the function. It currently returns a pointer to a stack
// variable, which is a dangling pointer!

int *make_value() {
  int x = 42;
  return &x;
}

TEST_CASE("stack vs heap") {
  int *p = make_value();
  CHECK(*p == 42);
  delete p;
}

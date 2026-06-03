#include <doctest/doctest.h>

// TODO: Implement a variadic function template 'count_args' that
// takes any number of arguments and returns how many there are.
// Use sizeof...(args).

// TODO: define count_args here

TEST_CASE("variadic sizeof") {
  CHECK(count_args() == 0);
  CHECK(count_args(1) == 1);
  CHECK(count_args(1, 2, 3) == 3);
  CHECK(count_args(1, 'a', 3.0, true) == 4);
}

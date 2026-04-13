#include <doctest/doctest.h>
//
// TODO: Implement a function that takes a reference to an array of
// exactly 4 ints and returns the sum of all elements.

int sum_of_four(?) {
    return 0; 
}

TEST_CASE("reference to array") {
  int a[] = {10, 20, 30, 40};
  CHECK(sum_of_four(a) == 100);

  // int b[] = {1, 2, 3}; // this should NOT compile due to wrong size!
}

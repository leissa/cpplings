#include <algorithm>
#include <doctest/doctest.h>

// TODO: Create a function sort_descending that sorts the array in DESCENDING
// order using std::sort with a lambda comparator. Make sure to match the call
// in the TEST_CASE
//
// Hint:  void std::sort( RandomIt first, RandomIt last, Compare comp );

TEST_CASE("lambda sort") {
  int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
  sort_descending(arr, 8);
  CHECK(arr[0] == 9);
  CHECK(arr[1] == 6);
  CHECK(arr[2] == 5);
  CHECK(arr[7] == 1);
}

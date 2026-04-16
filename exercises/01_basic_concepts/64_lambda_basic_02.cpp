#include <doctest/doctest.h>

// TODO: Implement count_if that counts how many elements in the array
// satisfy a condition, using a lambda that captures a counter by reference.

int count_greater_than(int *arr, int size, int threshold) {
  int count = 0;

  return count;
}

TEST_CASE("lambda capture by reference") {
  int arr[] = {1, 5, 3, 8, 2, 7};
  CHECK(count_greater_than(arr, 6, 4) == 3);
  CHECK(count_greater_than(arr, 6, 0) == 6);
  CHECK(count_greater_than(arr, 6, 10) == 0);
}

#include <doctest/doctest.h>

// TODO: Fix the function. It should NOT modify the array values.
// Change the parameter type to enforce this at compile time.

int sum_array(int *arr, int size) {
  int total = 0;
  for (int i = 0; i < size; i++) {
    total += arr[i];
  }
  return total;
}

TEST_CASE("const pointer") {
  const int arr[] = {10, 20, 30};
  CHECK(sum_array(arr, 3) == 60);
}

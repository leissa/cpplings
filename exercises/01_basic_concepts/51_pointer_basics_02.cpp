#include <doctest/doctest.h>

// TODO: Use pointer arithmetic (not the subscript operator) to return
// the third element of the array.

int third_element(int *arr) {
  return arr[2]; // TODO: rewrite using pointer arithmetic (*(ptr + n) form)
}

TEST_CASE("pointer arithmetic") {
  int arr[] = {10, 20, 30, 40};
  CHECK(third_element(arr) == 30);
}

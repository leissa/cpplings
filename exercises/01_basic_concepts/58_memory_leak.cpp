#include <doctest/doctest.h>

// TODO: Fix compute_sum so that the memory allocated by allocate_and_fill
// is properly freed after use. Do not modify allocate_and_fill.

int *allocate_and_fill(int n, int value) {
  int *arr = new int[n];
  for (int i = 0; i < n; i++)
    arr[i] = value;
  return arr;
}

int compute_sum(int n, int value) {
  int *arr = allocate_and_fill(n, value);
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += arr[i];
  return sum;
}

TEST_CASE("no memory leak") {
  CHECK(compute_sum(5, 10) == 50);
  CHECK(compute_sum(3, 7) == 21);
  CHECK(compute_sum(1, 42) == 42);
}

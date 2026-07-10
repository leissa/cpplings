#include <deque>
#include <doctest/doctest.h>
#include <functional>
#include <queue>
#include <vector>

// TODO: Implement kth_largest that takes a vector of ints and an int k,
// and returns the k-th largest element (1-based: k=1 is the largest).

int kth_largest(const std::vector<int> &nums, int k) {
  return 0; // TODO
}

// TODO: Implement kth_largest_deque, identical algorithm to kth_largest
// but use std::deque as the underlying container instead of std::vector.

int kth_largest_deque(const std::vector<int> &nums, int k) {
  return 0; // TODO
}

TEST_CASE("kth largest element") {
  CHECK(kth_largest({3, 2, 1, 5, 6, 4}, 2) == 5);
  CHECK(kth_largest({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4) == 4);
  CHECK(kth_largest({1}, 1) == 1);
}

TEST_CASE("kth largest with deque underlying container") {
  // same results — underlying container is an implementation detail
  CHECK(kth_largest_deque({3, 2, 1, 5, 6, 4}, 2) == 5);
  CHECK(kth_largest_deque({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4) == 4);
  CHECK(kth_largest_deque({1}, 1) == 1);
}

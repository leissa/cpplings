// exercise: sliding_window.cpp
#include <algorithm>
#include <deque>
#include <doctest/doctest.h>
#include <vector>

// TODO: Implement sliding_max(nums, k) that returns a vector<int>
// containing the maximum of each window of size k.
//
// Hint: use a std::deque to maintain indices of useful elements.
// The deque stores indices in decreasing order of their values.
//
std::vector<int> sliding_max(const std::vector<int> &nums, int k) {
  return {}; // TODO
}

TEST_CASE("sliding window maximum") {
  auto r1 = sliding_max({1, 3, -1, -3, 5, 3, 6, 7}, 3);
  CHECK(r1.size() == 6);
  CHECK(r1[0] == 3);
  CHECK(r1[1] == 3);
  CHECK(r1[2] == 5);
  CHECK(r1[3] == 5);
  CHECK(r1[4] == 6);
  CHECK(r1[5] == 7);

  auto r2 = sliding_max({1, 2, 3}, 1);
  CHECK(r2 == std::vector<int>{1, 2, 3});
}

#include <doctest/doctest.h>
#include <numeric>
#include <ranges>
#include <vector>

// TODO: Implement range_sum_query that:
//   1. Takes a vector<int> nums and builds a prefix sum vector
//      using std::partial_sum
//   2. Returns a lambda [prefix](int l, int r) -> int
//      that returns the sum of nums[l..r] (inclusive, 0-indexed)
//      in O(1) using the prefix sum array.

auto range_sum_query(const std::vector<int> &nums) {
  // TODO: build prefix sums and return a capturing lambda
  return [](int, int) { return 0; };
}

TEST_CASE("prefix sum range query") {
  std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
  auto query = range_sum_query(nums);

  CHECK(query(0, 0) == 3);
  CHECK(query(0, 3) == 9);
  CHECK(query(2, 5) == 19);
  CHECK(query(0, 7) == 31);
}

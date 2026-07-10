#include <algorithm>
#include <doctest/doctest.h>
#include <numeric>
#include <vector>

// TODO: Implement the following function that:
//   1. Takes a vector of ints by value
//   2. Removes all elements less than `threshold` using the
//      erase-remove idiom
//   3. Sorts the remaining elements in descending order
//   4. Returns the modified vector

std::vector<int> filter_and_sort(std::vector<int> vec, int threshold) {
  return {}; // TODO
}

TEST_CASE("vector filter and sort") {
  std::vector<int> v = {5, 1, 8, 3, 9, 2, 7, 4, 6};
  std::vector<int> result = filter_and_sort(v, 4);

  std::vector<int> expected = {9, 8, 7, 6, 5};
  CHECK(expected == result);

  // original is unchanged (passed by value)
  CHECK(v.size() == 9);
}

#include <algorithm>
#include <doctest/doctest.h>
#include <set>
#include <vector>

// TODO: Implement function 'common_elements' that takes two vectors of ints and
// returns a sorted std::vector<int> of elements appearing in both vectors,
// with no duplicates.
// Hint:
//   1. Convert both vectors to std::set to remove duplicates
//   2. Use intersection to find common elements

TEST_CASE("set intersection") {
  std::vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
  std::vector<int> b = {5, 3, 5, 8, 9, 7, 9, 3};
  auto result = common_elements(a, b);

  CHECK(result.size() == 3);
  CHECK(result[0] == 3);
  CHECK(result[1] == 5);
  CHECK(result[2] == 9);
}

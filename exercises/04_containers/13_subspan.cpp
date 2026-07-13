#include <algorithm>
#include <array>
#include <doctest/doctest.h>
#include <numeric>
#include <span>

// TODO: Implement row_sums(matrix, cols)
//   Interprets the flat span as a row-major matrix with 'cols' columns.
//   Returns a vector<int> where result[i] is the sum of row i.
//   Use span::subspan to extract each row

std::vector<int> row_sums(std::span<const int> matrix, std::size_t cols) {
  return {}; // TODO
}

// TODO: Implement contains_subseq(data, pattern)
//   Returns true if pattern appears as a contiguous subsequence in data.
//   Use span::first / span::last / span::subspan to extract windows.
//   Hint: for each position i, you can take data.subspan(i, pattern.size())

bool contains_subseq(std::span<const int> data, std::span<const int> pattern) {
  return false; // TODO
}

TEST_CASE("span row sums") {
  // 3x4 matrix stored row-major:
  // 1  2  3  4
  // 5  6  7  8
  // 9 10 11 12
  std::vector<int> matrix = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  auto sums = row_sums(matrix, 4);
  CHECK(sums == std::vector<int>{10, 26, 42});

  // also works with a raw array
  int arr[] = {1, 2, 3, 4, 5, 6};
  auto sums2 = row_sums(arr, 2);
  CHECK(sums2 == std::vector<int>{3, 7, 11});
}

TEST_CASE("span contains subsequence") {
  std::vector<int> data = {1, 2, 3, 4, 5, 6};
  std::vector<int> pattern = {3, 4, 5};
  CHECK(contains_subseq(data, pattern) == true);

  std::vector<int> missing = {3, 5};
  CHECK(contains_subseq(data, missing) == false);

  // pattern longer than data
  std::vector<int> too_long = {1, 2, 3, 4, 5, 6, 7};
  CHECK(contains_subseq(data, too_long) == false);

  // works with std::array too
  std::array<int, 4> arr = {10, 20, 30, 40};
  std::array<int, 2> pat = {20, 30};
  CHECK(contains_subseq(arr, pat) == true);
}

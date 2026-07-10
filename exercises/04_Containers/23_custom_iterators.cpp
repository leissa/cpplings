#include <algorithm>
#include <doctest/doctest.h>
#include <numeric>

// TODO: Implement a class 'Stride' that iterates over integers
// from 'start' to 'stop' (exclusive) with a given 'step'.
// For example, Stride(0, 10, 3) iterates: 0, 3, 6, 9
//
// Stride must provide:
//   - begin() returning an iterator at 'start'
//   - end()   returning a sentinel iterator at 'stop'
//   - iterator with:  operator*,
//                     operator!=,
//                     operator==,
//                     prefix operator++

// TODO: define Stride here

TEST_CASE("custom stride iterator") {
  Stride s(0, 10, 3);

  std::vector<int> result;
  for (int v : s)
    result.push_back(v);

  CHECK(result.size() == 4);
  CHECK(result[0] == 0);
  CHECK(result[1] == 3);
  CHECK(result[2] == 6);
  CHECK(result[3] == 9);

  // works with std algorithms
  int sum = std::accumulate(s.begin(), s.end(), 0);
  CHECK(sum == 18);

  auto it = std::find(s.begin(), s.end(), 6);
  CHECK(*it == 6);
}

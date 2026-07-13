#include <doctest/doctest.h>
#include <numeric>
#include <string>
#include <vector>

// TODO: Implement these three functions using std::accumulate:
//
// product(vec)   returns the product of all elements
// flatten(vecs)  concatenates a vector<vector<int>> into a vector<int>
// join(words, sep) joins strings with a separator

int product(const std::vector<int> &vec) {
  return 0; // TODO
}

std::vector<int> flatten(const std::vector<std::vector<int>> &vecs) {
  return {}; // TODO
}

std::string join(const std::vector<std::string> &words,
                 const std::string &sep) {
  return ""; // TODO
}

TEST_CASE("std::accumulate product") {
  CHECK(product({1, 2, 3, 4, 5}) == 120);
  CHECK(product({2, 3}) == 6);
}

TEST_CASE("std::accumulate flatten") {
  CHECK(flatten({{1, 2}, {3}, {4, 5, 6}}) ==
        std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("std::accumulate join") {
  CHECK(join({"one", "two", "three"}, ", ") == "one, two, three");
  CHECK(join({"only"}, "-") == "only");
}

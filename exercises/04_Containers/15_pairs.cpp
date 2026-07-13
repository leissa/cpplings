// exercise: pair_tuple.cpp
#include <algorithm>
#include <doctest/doctest.h>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// TODO: Implement stats(vec)
//   Returns a std::tuple<int, int, double> of {min, max, mean}.

std::tuple<int, int, double> stats(const std::vector<int> &vec) {
  return {}; // TODO
}

// TODO: Implement sort_by(words)
//   Takes a vector of strings by value.
//   Sorts by (length, alphabetical) using a vector of pairs.
//   Returns the sorted vector of strings.

std::vector<std::string> sort_by(std::vector<std::string> words) {
  return {}; // TODO
}

TEST_CASE("stats tuple with structured bindings") {
  auto [mn, mx, mean] = stats({3, 1, 4, 1, 5, 9, 2, 6});
  CHECK(mn == 1);
  CHECK(mx == 9);
  CHECK(mean == doctest::Approx(3.875));

  auto [mn2, mx2, mean2] = stats({42});
  CHECK(mn2 == 42);
  CHECK(mx2 == 42);
  CHECK(mean2 == doctest::Approx(42.0));
}

TEST_CASE("sort by length then alphabetical") {
  auto result = sort_by({"banana", "fig", "apple", "kiwi", "plum"});
  CHECK(result ==
        std::vector<std::string>{"fig", "kiwi", "plum", "apple", "banana"});
}

#include <doctest/doctest.h>
#include <numeric>
#include <ranges>
#include <vector>

// TODO: Implement even_take(vec, n)
//   Takes a vector<int> and an int n.
//   Returns a vector<int> of the first n even numbers in vec.
//   Use: std::views::filter then std::views::take
//
// TODO: Implement sum_of_squares(vec)
//   Takes a vector<int>.
//   Returns the sum of squares of all elements.
//   Use: std::views::transform then std::ranges::fold_left

std::vector<int> even_take(const std::vector<int> &vec, int n) {
  return {}; // TODO
}

int sum_of_squares(const std::vector<int> &vec) {
  return 0; // TODO
}

TEST_CASE("ranges filter and take") {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto result = even_take(v, 3);
  CHECK(result == std::vector<int>{2, 4, 6});
}

TEST_CASE("ranges transform and fold") {
  std::vector<int> v = {1, 2, 3, 4, 5};
  CHECK(sum_of_squares(v) == 55);
}

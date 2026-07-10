#include <doctest/doctest.h>
#include <numeric>
#include <span>

// TODO: Implement running_sum(data, out)
//   Takes std::span<const int> data and std::span<int> out.
//   Fills out[i] with the sum of data[0..i] (inclusive).
//   Assume out.size() == data.size().

void running_sum(std::span<const int> data, std::span<int> out) {
  // TODO
}

// TODO: Implement trim(data, n)
//   Returns a span with the first n and last n elements removed.
//   i.e. data.subspan(n, data.size() - 2 * n)

std::span<const int> trim(std::span<const int> data, std::size_t n) {
  return {}; // TODO
}

TEST_CASE("span running sum") {
  std::vector<int> data = {1, 2, 3, 4, 5};
  std::vector<int> out(5);
  running_sum(data, out);
  CHECK(out == std::vector<int>{1, 3, 6, 10, 15});
}

TEST_CASE("span subspan trim") {
  std::vector<int> v = {10, 20, 30, 40, 50, 60, 70};
  auto trimmed = trim(v, 2);
  CHECK(trimmed.size() == 3);
  CHECK(trimmed[0] == 30);
  CHECK(trimmed[1] == 40);
  CHECK(trimmed[2] == 50);
}

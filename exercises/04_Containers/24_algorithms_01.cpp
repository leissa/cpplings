#include <algorithm>
#include <doctest/doctest.h>
#include <string>
#include <vector>

// TODO: Implement two functions:
//
// normalize(vec)
//   Takes a vector<double> by value.
//   Divides every element by the maximum element using std::transform.
//   Returns the normalized vector.
//
// to_lengths(words)
//   Takes a const vector<string> by reference.
//   Returns a vector<int> of word lengths using std::transform.
//
// Note: assume vec is non-empty and the max element is non-zero.

TEST_CASE("std::transform normalize") {
  auto normed = normalize({2.0, 4.0, 8.0, 6.0});
  CHECK(normed[0] == doctest::Approx(0.25));
  CHECK(normed[1] == doctest::Approx(0.5));
  CHECK(normed[2] == doctest::Approx(1.0));
  CHECK(normed[3] == doctest::Approx(0.75));
}

TEST_CASE("std::transform to lengths") {
  auto lengths = to_lengths({"hello", "hi", "hey", "aloha", "hola"});
  CHECK(lengths == std::vector<int>{5, 2, 3, 5, 4});
}

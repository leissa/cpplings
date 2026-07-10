#include <doctest/doctest.h>
#include <map>
#include <string>
#include <vector>

// TODO: Implement word_frequency that takes a vector of strings and
// returns a std::map<std::string, int> mapping each word to its
// number of occurrences.

std::map<std::string, int>
word_frequency(const std::vector<std::string> &words) {
  return {}; // TODO
}

TEST_CASE("map word frequency") {
  std::vector<std::string> words = {"to", "be", "or", "not", "to", "be", "to"};
  auto freq = word_frequency(words);

  CHECK(freq.at("to") == 3);
  CHECK(freq.at("be") == 2);
  CHECK(freq.at("or") == 1);
  CHECK(freq.at("not") == 1);

  CHECK(freq.count("hamlet") == 0);
  CHECK(freq.size() == 4);
}

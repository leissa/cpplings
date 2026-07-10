#include <algorithm>
#include <doctest/doctest.h>
#include <map>
#include <string>
#include <vector>

// TODO: Implement group_by_first_letter that takes a vector of strings
// and returns a map from char (first letter) to vector<string> of all
// words starting with that letter.

std::map<char, std::vector<std::string>>
group_by_first_letter(const std::vector<std::string> &words) {
  return {}; // TODO
}

TEST_CASE("group by first letter") {
  auto groups = group_by_first_letter(
      {"apple", "banana", "avocado", "blueberry", "cherry", "apricot"});

  CHECK(groups['a'].size() == 3);
  CHECK(groups['b'].size() == 2);
  CHECK(groups['c'].size() == 1);
  CHECK(groups.count('d') == 0);

  // words within each group appear in insertion order
  CHECK(groups['a'][0] == "apple");
  CHECK(groups['a'][1] == "avocado");
  CHECK(groups['a'][2] == "apricot");
}

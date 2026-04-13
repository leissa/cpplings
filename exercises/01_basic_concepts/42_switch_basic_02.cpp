#include <doctest/doctest.h>

// TODO: Implement a function that counts weekend days using fallthrough.
// SATURDAY and SUNDAY should both result in returning true (is_weekend).

enum class Day { MON, TUE, WED, THU, FRI, SAT, SUN };

bool is_weekend(Day d) { return false; }

TEST_CASE("switch fallthrough") {
  CHECK_FALSE(is_weekend(Day::MON));
  CHECK_FALSE(is_weekend(Day::FRI));
  CHECK(is_weekend(Day::SAT));
  CHECK(is_weekend(Day::SUN));
}

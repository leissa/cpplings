#include <doctest/doctest.h>

int value() { return 42; }

namespace my_ns {
int value() { return 7; }

// TODO: Implement this function so it returns the GLOBAL value(),
// not my_ns::value().
int get_global_value() { return value(); }
} // namespace my_ns

TEST_CASE("global namespace") {
  CHECK(my_ns::get_global_value() == 42);
  CHECK(my_ns::value() == 7);
}

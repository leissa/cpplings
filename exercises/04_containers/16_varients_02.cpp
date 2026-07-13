#include <doctest/doctest.h>
#include <format>
#include <optional>
#include <string>
#include <variant>
#include <vector>

// TODO: Implement describe_variant
//   Takes std::variant<int, double, std::string>
//   Returns:
//     "int: N"    if it holds an int
//     "double: X" if it holds a double (1 decimal place)
//     "string: S" if it holds a string
//   Use std::visit.

std::string describe_variant(std::variant<int, double, std::string> v) {
  return ""; // TODO
}

// TODO: Implement safe_divide(a, b)
//   Returns std::nullopt if b == 0.
//   Otherwise returns a / b.

std::optional<double> safe_divide(double a, double b) {
  return std::nullopt; // TODO
}

// TODO: Implement first_even(vec)
//   Returns std::optional<int>, the first even element in vec,
//   or std::nullopt if none exists.

std::optional<int> first_even(const std::vector<int> &vec) {
  return std::nullopt; // TODO
}

TEST_CASE("variant describe") {
  CHECK(describe_variant(42) == "int: 42");
  CHECK(describe_variant(3.14) == "double: 3.1");
  CHECK(describe_variant(std::string("hi")) == "string: hi");
}

TEST_CASE("optional safe_divide") {
  CHECK(safe_divide(10.0, 4.0).value() == doctest::Approx(2.5));
  CHECK(safe_divide(1.0, 0.0) == std::nullopt);

  // value_or provides a default when nullopt
  CHECK(safe_divide(1.0, 0.0).value_or(-1.0) == doctest::Approx(-1.0));
  CHECK(safe_divide(6.0, 2.0).value_or(-1.0) == doctest::Approx(3.0));
}

TEST_CASE("optional first even") {
  CHECK(first_even({1, 3, 4, 7}) == 4);
  CHECK(first_even({1, 3, 5}) == std::nullopt);
  CHECK(first_even({}) == std::nullopt);
}

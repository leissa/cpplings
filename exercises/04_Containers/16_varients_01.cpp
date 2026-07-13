#include <doctest/doctest.h>
#include <format>
#include <string>
#include <variant>
#include <vector>

using Number = std::variant<int, double>;

// TODO: Implement to_double(n)
//   Converts a Number to double regardless of which type it holds.
//   Use std::visit.

double to_double(Number n) {
  return 0.0; // TODO
}

// TODO: Implement add(a, b)
//   Adds two Numbers.
//   If both are int, return an int result. Return double otherwise.
//   Hint: use std::visit with two arguments .

Number add(Number a, Number b) {
  return 0; // TODO
}

// TODO: Implement is_integer(n)
//   Returns true if n currently holds an int.
//   Use std::holds_alternative.
bool is_integer(Number n) {
  return false; // TODO
}

// TODO: Implement format_number(n)
//   Returns "int(N)" if n holds an int
//   Returns "double(X)" with 2 decimal places if n holds a double.
//   Use std::visit and std::format.

std::string format_number(Number n) {
  return ""; // TODO
}

TEST_CASE("variant to_double") {
  CHECK(to_double(Number{42}) == doctest::Approx(42.0));
  CHECK(to_double(Number{3.14}) == doctest::Approx(3.14));
}

TEST_CASE("variant add") {
  // int + int -> int
  Number r1 = add(Number{3}, Number{4});
  CHECK(is_integer(r1));
  CHECK(std::get<int>(r1) == 7);

  // int + double -> double
  Number r2 = add(Number{3}, Number{1.5});
  CHECK(!is_integer(r2));
  CHECK(std::get<double>(r2) == doctest::Approx(4.5));

  // double + double -> double
  Number r3 = add(Number{1.5}, Number{2.5});
  CHECK(!is_integer(r3));
  CHECK(std::get<double>(r3) == doctest::Approx(4.0));
}

TEST_CASE("variant is_integer") {
  CHECK(is_integer(Number{42}) == true);
  CHECK(is_integer(Number{3.14}) == false);
}

TEST_CASE("variant format_number") {
  CHECK(format_number(Number{42}) == "int(42)");
  CHECK(format_number(Number{3.14}) == "double(3.14)");
  CHECK(format_number(Number{-7}) == "int(-7)");
}

#include <doctest/doctest.h>
#include <string>

// TODO: Define a class template 'Pair<T, R>' with:
//   - PUBLIC members 'first' of type T and 'second' of type R
//   - a constructor taking T and R
//
// The default deduction would make Pair("hello", "world") deduce
// Pair<const char*, const char*>. That is not ideal for strings.
//
// TODO: Add a deduction guide so that when both arguments are
// const char*, the pair is deduced as Pair<std::string, std::string>
// instead.

// TODO: define Pair and deduction guide here

TEST_CASE("ctad basic") {
  Pair p1(3, 3.14); // deduced as Pair<int, double>
  static_assert(std::is_same_v<decltype(p1.first), int>);
  static_assert(std::is_same_v<decltype(p1.second), double>);
  CHECK(p1.first == 3);
  CHECK(p1.second == doctest::Approx(3.14));
}

TEST_CASE("ctad deduction guide") {
  Pair p2("hello", "world"); // guided to Pair<std::string, std::string>
  static_assert(std::is_same_v<decltype(p2.first), std::string>);
  static_assert(std::is_same_v<decltype(p2.second), std::string>);
  CHECK(p2.first == "hello");
  CHECK(p2.second == "world");
}

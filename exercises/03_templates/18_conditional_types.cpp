#include <doctest/doctest.h>
#include <type_traits>

// TODO: Define a template alias 'Storage<T>' that:
//   - is long long if sizeof(T) > 4
//   - is int otherwise
//
// TODO: Implement a function template 'promote(T value)' that:
//   - returns value cast to Storage<T>

// TODO: define Storage and promote here

TEST_CASE("conditional type") {
  // char is small -> stored as int
  static_assert(std::is_same_v<Storage<char>, int>);
  auto r1 = promote('A');
  static_assert(std::is_same_v<decltype(r1), int>);
  CHECK(r1 == 65);

  // int is small -> stored as int
  static_assert(std::is_same_v<Storage<int>, int>);
  auto r2 = promote(42);
  static_assert(std::is_same_v<decltype(r2), int>);
  CHECK(r2 == 42);

  // double is large -> stored as long long
  static_assert(std::is_same_v<Storage<double>, long long>);
  auto r3 = promote(3.7);
  static_assert(std::is_same_v<decltype(r3), long long>);
  CHECK(r3 == 3ll);
}

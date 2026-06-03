#include <doctest/doctest.h>
#include <type_traits>

// TODO: Implement two overloads of 'describe_type':
//   1. Returns "signed"   for signed arithmetic types
//      Use: std::enable_if_t<std::is_signed_v<T>>
//   2. Returns "unsigned" for unsigned arithmetic types
//      Use: std::enable_if_t<!std::is_signed_v<T>>

// TODO: define describe_type here

TEST_CASE("sfinae enable_if") {
  CHECK(std::string(describe_type(1)) == "signed");
  CHECK(std::string(describe_type(1.0)) == "signed");
  CHECK(std::string(describe_type(1u)) == "unsigned");
  CHECK(std::string(describe_type(true)) == "unsigned");
}

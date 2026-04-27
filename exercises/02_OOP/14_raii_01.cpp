#include <cstring>
#include <doctest/doctest.h>

// RAII: Resource Acquisition Is Initialization.
// Acquire a resource in the constructor, release it in the destructor.
// This ensures no resource leaks even if the code exits early.
//
// TODO: Define a class `String` that manages a heap-allocated char array.
//   - constructor takes a const char* and copies it into a new[] char array
//   - copy constructor performs a deep copy
//   - destructor frees the array with delete[]
//   - a const member function `length()` returns the string length
//   - a const member function `at(int i)` returns the character at index i
//   - a member function 'set(int i, char c)' to set a the char at index i to c

// TODO: define String here

TEST_CASE("raii string") {
  String s1("hello");
  CHECK(s1.length() == 5);
  CHECK(s1.at(0) == 'h');
  CHECK(s1.at(4) == 'o');

  String s2(s1);
  CHECK(s2.length() == 5);
  s2.set(1, 'a');
  CHECK(s2.at(0) == 'h');
  CHECK(s1.at(1) != 'a');
}

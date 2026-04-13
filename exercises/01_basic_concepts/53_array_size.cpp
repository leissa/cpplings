#include <cstddef>
#include <doctest/doctest.h>

// TODO: Return the number of elements in the array.

template <typename T, std::size_t N> std::size_t array_length(T (&)[N]) {
  return 0;
}

TEST_CASE("array size") {
  int a[] = {1, 2, 3, 4, 5};
  CHECK(array_length(a) == 5);

  double b[] = {1.0, 2.0};
  CHECK(array_length(b) == 2);
}

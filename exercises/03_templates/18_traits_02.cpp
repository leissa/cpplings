#include <doctest/doctest.h>
#include <type_traits>

// TODO: Use the following type traits to transform built-in types:
// std::make_unsigned_t<T>
// std::remove_const_t<T>
// std::add_pointer_t<T>
// std::remove_pointer_t<T*>
//
// TODO: Define the following type aliases using the correct trait:
//   - 'U'   the unsigned version of int
//   - 'NC'  the non-const version of const double
//   - 'P'   a pointer to float
//   - 'D'   the type that float* points to

// TODO: define aliases here

TEST_CASE("type manipulation") {
  static_assert(std::is_same_v<U, unsigned int>);
  static_assert(std::is_same_v<NC, double>);
  static_assert(std::is_same_v<P, float *>);
  static_assert(std::is_same_v<D, float>);

  CHECK(true);
}

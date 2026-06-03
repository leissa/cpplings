#include <doctest/doctest.h>

// TODO: Define a class template 'Box' with:
//   - a single type parameter T
//   - a PRIVATE member 'value' of type T
//   - a constructor taking a T
//   - a PUBLIC const function 'get()' returning the value
//   - a PUBLIC function 'set(T v)' updating the value

// TODO: define Box here

TEST_CASE("class template basic") {
  Box<int> bi(42);
  CHECK(bi.get() == 42);
  bi.set(10);
  CHECK(bi.get() == 10);

  Box<double> bd(3.14);
  CHECK(bd.get() == doctest::Approx(3.14));
  bd.set(2.71);
  CHECK(bd.get() == doctest::Approx(2.71));

  Box<char> bc('z');
  CHECK(bc.get() == 'z');
}

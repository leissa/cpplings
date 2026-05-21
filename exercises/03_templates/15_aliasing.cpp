#include <doctest/doctest.h>

// TODO: Define the following aliases:
//   - 'Byte'           as an alias for unsigned char
//   - template alias 'Buffer<N>' for a Byte array of size N
//   - template alias 'Pair<T>' for a struct with two T members: first, second
// Then implement:
//   - int  byte_value(Byte b) returns b as int
//   - template function 'buffer_sum' takes a const reference to a Buffer<N> and
//   returns the sum of all elements as int

// TODO: define aliases and implement functions here

TEST_CASE("using alias") {
  Byte b = 255;
  CHECK(byte_value(b) == 255);

  Buffer<4> buf4 = {10, 20, 30, 40};
  CHECK(buffer_sum(buf4) == 100);

  Buffer<2> buf2 = {99, 88};
  CHECK(buffer_sum(buf2) == 187);

  Pair<int> pi{3, 7};
  CHECK(pi.first + pi.second == 10);

  Pair<double> pd{1.5, 2.5};
  CHECK(pd.first + pd.second == doctest::Approx(4.0));
}

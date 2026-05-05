#include <doctest/doctest.h>

// TODO: Define a struct `Clamp` with:
//   - constructor taking `lo` and `hi` doubles
//   - const operator() that takes a double and returns it clamped to [lo, hi]

struct Clamp {
  // TODO
};

TEST_CASE("function call operator") {
  Clamp clamp01{0.0, 1.0};
  CHECK(clamp01(-0.5) == doctest::Approx(0.0));
  CHECK(clamp01(0.5) == doctest::Approx(0.5));
  CHECK(clamp01(1.5) == doctest::Approx(1.0));

  Clamp clamp05{0.0, 5.0};
  CHECK(clamp05(3.0) == doctest::Approx(3.0));
  CHECK(clamp05(10.0) == doctest::Approx(5.0));
}

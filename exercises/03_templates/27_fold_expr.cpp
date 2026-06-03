#include <doctest/doctest.h>

// TODO: Implement these three functions using folding expressions:
//   - 'sum_all(args...)' returns the sum using unary fold
//   - 'product_all(args...)' returns the product using unary fold
//   - 'all_positive(args...)' returns true if all args > 0, using && fold

// TODO: define sum_all, product_all, all_positive here

TEST_CASE("fold expressions") {
  CHECK(sum_all(1, 2, 3, 4) == 10);
  CHECK(sum_all(1.5, 2.5) == doctest::Approx(4.0));

  CHECK(product_all(1, 2, 3, 4) == 24);
  CHECK(product_all(2, 3) == 6);

  CHECK(all_positive(1, 2, 3) == true);
  CHECK(all_positive(1, -1, 3) == false);
  CHECK(all_positive(0, 1, 2) == false);
}

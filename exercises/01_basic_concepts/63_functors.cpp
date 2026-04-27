
// A function object (functor) is a struct/class that overloads operator().
// TODO: Implement a functor called Multiplier whose constructor takes
// a factor, and whose operator() multiplies the input by that factor.

struct Multiplier {
}

TEST_CASE("functor") {
  Multiplier triple(3);
  Multiplier times_ten(10);
  CHECK(triple(5) == 15);
  CHECK(times_ten(5) == 50);
  CHECK(triple(0) == 0);
}

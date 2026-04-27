#include <doctest/doctest.h>

// TODO: Implement a lambda that computes the nth Fibonacci number.
// fib(0) = 0, fib(1) = 1, fib(n) = fib(n-1) + fib(n-2)

auto fib = ? ;

TEST_CASE("lambda recursion fibonacci") {
  CHECK(fib(0, fib) == 0);
  CHECK(fib(1, fib) == 1);
  CHECK(fib(2, fib) == 1);
  CHECK(fib(5, fib) == 5);
  CHECK(fib(10, fib) == 55);
}

#include <doctest/doctest.h>

// TODO: Define a class template 'Stack' with:
//   - a type parameter T for the element type
//   - a non-type template parameter int N (the maximum capacity)
//   - a PRIVATE fixed-size array T data[N] and int count (initialized to 0)
//   - PUBLIC functions:
//       void push(T v)     stores v at data[count], increments count
//       T    pop()         decrements count, returns data[count]
//       int  size() const  returns count

// TODO: define Stack here

TEST_CASE("class template nttp") {
  Stack<int, 5> s;
  CHECK(s.size() == 0);

  s.push(10);
  s.push(20);
  s.push(30);
  CHECK(s.size() == 3);

  CHECK(s.pop() == 30);
  CHECK(s.pop() == 20);
  CHECK(s.size() == 1);
}

#include <doctest/doctest.h>

// TODO: Define:
//   - struct Animal with a virtual destructor
//   - struct Dog : Animal with a function `fetch()` returning "fetching"
//   - struct Cat : Animal with a function `purr()` returning "purring"
//
//
// TODO: Implement `try_fetch` that takes an Animal* and returns "fetching"
// if the animal is a Dog, or "not a dog" otherwise. Use dynamic_cast.

TEST_CASE("dynamic cast") {
  Animal *d = new Dog();
  Animal *c = new Cat();

  CHECK(try_fetch(d) == doctest::String("fetching"));
  CHECK(try_fetch(c) == doctest::String("not a dog"));

  delete d;
  delete c;
}

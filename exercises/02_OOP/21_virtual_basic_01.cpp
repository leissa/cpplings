#include <doctest/doctest.h>

// TODO: Use the virtual functions to make the dispatch work correctly.

struct Animal {
  const char *speak() { return "..."; }
};

struct Dog : Animal {
  const char *speak() { return "woof"; }
};

struct Cat : Animal {
  const char *speak() { return "meow"; }
};

const char *make_speak(Animal &a) { return a.speak(); }

TEST_CASE("virtual dispatch") {
  Dog d;
  Cat c;
  CHECK(make_speak(d) == doctest::String("woof"));
  CHECK(make_speak(c) == doctest::String("meow"));
}

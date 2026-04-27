#include <doctest/doctest.h>

// TODO: Add override to the derived methods, and fix any signature
// mismatches that override reveals.

struct Shape {
  virtual double area() const { return 0.0; }
  virtual const char *name() const { return "shape"; }
};

struct Square : Shape {
  double side;
  Square(double s) : side(s) {}
  double area() { return side * side; }
  const char *Name() const { return "square"; }
};

double total_area(Shape &s) { return s.area(); }

TEST_CASE("override") {
  Square sq(4.0);
  CHECK(total_area(sq) == doctest::Approx(16.0));
  CHECK(sq.name() == doctest::String("square"));
}

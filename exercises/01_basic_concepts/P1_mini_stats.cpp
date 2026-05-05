// project: mini_stats
//
// Build a small statistics library that operates on dynamic arrays of doubles.
// Work through each part in order — later parts reuse earlier ones.
// Do not modify the TEST_CASEs.

#include <algorithm>
#include <cmath>
#include <doctest/doctest.h>

// ============================================================================
// PART 1: Define the data types
// ============================================================================

// TODO: Define an enum class `Stat` with values: MIN, MAX, MEAN, SUM.

// TODO: Define a struct `Result` with:
//   - a Stat member called `kind`
//   - a double member called `value` (default initialized to 0.0)

TEST_CASE("Part 1: types") {
  Result r{Stat::SUM, 3.14};
  CHECK(r.kind == Stat::SUM);
  CHECK(r.value == doctest::Approx(3.14));

  Result r2{Stat::MIN};
  CHECK(r2.value == doctest::Approx(0.0));
}

// ============================================================================
// PART 2: Dynamic array helpers
// ============================================================================

// TODO: Implement allocate_and_copy.
// Allocate a new double array on the heap with `new[]`,
// copy `size` elements from `src` into it, and return the new array.

double *allocate_and_copy(const double *src, int size) {
  return nullptr; // TODO
}

TEST_CASE("Part 2: heap memory") {
  double src[] = {1.0, 2.0, 3.0, 4.0};
  double *copy = allocate_and_copy(src, 4);
  CHECK(copy != src);
  CHECK(copy[0] == doctest::Approx(1.0));
  CHECK(copy[2] == doctest::Approx(3.0));
  CHECK(copy[3] == doctest::Approx(4.0));
  delete[] copy;
}

// ============================================================================
// PART 3: Pass by-reference — find min and max
// ============================================================================

// TODO: Implement find_min_max.
// Write the minimum and maximum of the array into the reference parameters.

void find_min_max(const double *arr, int size, double &out_min,
                  double &out_max) {
  // TODO
}

TEST_CASE("Part 3: pass by reference") {
  double data[] = {3.0, -1.0, 4.0, 1.5, -2.0};
  double lo, hi;
  find_min_max(data, 5, lo, hi);
  CHECK(lo == doctest::Approx(-2.0));
  CHECK(hi == doctest::Approx(4.0));
}

// ============================================================================
// PART 4: Function overloading — summarize
// ============================================================================

// TODO: Implement two overloads of `summarize`:
// 1) summarize(arr, size)        → returns Result{Stat::SUM, <sum>}
// 2) summarize(arr, size, kind)  → returns Result with the requested stat
//    Support MIN, MAX, MEAN, SUM.
//
// Hint: reuse find_min_max for MIN/MAX.

Result summarize(const double *arr, int size) {
  return {}; // TODO
}

Result summarize(const double *arr, int size, Stat kind) {
  return {}; // TODO
}

TEST_CASE("Part 4: overloading") {
  double data[] = {2.0, 8.0, 4.0, 6.0};

  auto r1 = summarize(data, 4);
  CHECK(r1.kind == Stat::SUM);
  CHECK(r1.value == doctest::Approx(20.0));

  auto [kind, value] = summarize(data, 4, Stat::MEAN);
  CHECK(kind == Stat::MEAN);
  CHECK(value == doctest::Approx(5.0));

  CHECK(summarize(data, 4, Stat::MIN).value == doctest::Approx(2.0));
  CHECK(summarize(data, 4, Stat::MAX).value == doctest::Approx(8.0));
}

// ============================================================================
// PART 5: Lambda — custom aggregation
// ============================================================================

// `aggregate` reduces an array to a single value by repeatedly combining
// the current accumulated result with the next element using a lambda.
//
// This is already implemented for you using a generic lambda. Templates will be
// covered in later chapters. You will need to pass lambdas into it below.
//
// Example trace for sum over {3, 1, 4}:
//   acc = 0.0
//   acc = fn(0.0, 3.0) = 3.0
//   acc = fn(3.0, 1.0) = 4.0
//   acc = fn(4.0, 4.0) = 8.0
//   return 8.0

auto aggregate = [](const double *arr, int size, double init, auto fn) {
  double acc = init;
  for (int i = 0; i < size; i++)
    acc = fn(acc, arr[i]);
  return acc;
};

TEST_CASE("Part 5: lambda aggregation") {
  double data[] = {3.0, 1.0, 4.0, 1.0, 5.0};

  // TODO: pass a lambda to compute the sum of all elements
  double sum =
      aggregate(data, 5, 0.0, [](double acc, double x) { return acc; });
  CHECK(sum == doctest::Approx(14.0));

  // TODO: pass a lambda to compute the product of all elements
  double product =
      aggregate(data, 5, 1.0, [](double acc, double x) { return acc; });
  CHECK(product == doctest::Approx(60.0));

  // TODO: pass a lambda to find the maximum element
  double mx =
      aggregate(data, 5, data[0], [](double acc, double x) { return acc; });
  CHECK(mx == doctest::Approx(5.0));
}

// ============================================================================
// PART 6: Lambda with capture — normalize an array
// ============================================================================

// TODO: Implement make_normalizer.
// It takes lo and hi and returns a lambda that maps x → (x - lo) / (hi - lo).

auto make_normalizer(double lo, double hi) {
  return [](double x) { return x; }; // TODO: fix
}

// TODO: Implement normalize.
// 1. Find min and max with find_min_max.
// 2. Create a normalizer lambda with make_normalizer.
// 3. Apply it to every element in place.

void normalize(double *arr, int size) {
  // TODO
}

TEST_CASE("Part 6: lambda capture and composition") {
  double data[] = {2.0, 8.0, 5.0, 10.0, 4.0};
  normalize(data, 5);
  CHECK(data[0] == doctest::Approx(0.0));
  CHECK(data[1] == doctest::Approx(0.75));
  CHECK(data[2] == doctest::Approx(0.375));
  CHECK(data[3] == doctest::Approx(1.0));
  CHECK(data[4] == doctest::Approx(0.25));
}

// ============================================================================
// PART 7: Putting it all together
// ============================================================================

// TODO: Implement full_pipeline.
// Given a source array and size:
// 1. allocate_and_copy the data (so the original is not modified).
// 2. normalize the copy.
// 3. Use aggregate with a lambda to compute the sum of squared values.
// 4. Free the copy with delete[].
// 5. Return the sum of squares.

double full_pipeline(const double *src, int size) {
  return 0.0; // TODO
}

TEST_CASE("Part 7: full pipeline") {
  double data[] = {0.0, 5.0, 10.0};
  double original[] = {0.0, 5.0, 10.0};

  double result = full_pipeline(data, 3);

  CHECK(result == doctest::Approx(1.25));

  // Original data must be unchanged
  CHECK(data[0] == doctest::Approx(original[0]));
  CHECK(data[1] == doctest::Approx(original[1]));
  CHECK(data[2] == doctest::Approx(original[2]));
}

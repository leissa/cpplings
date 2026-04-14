#include <doctest/doctest.h>

// TODO: Allocate an array of 5 ints on the heap, fill it with
// values 0..4, compute the sum, then deallocate properly.

int heap_sum() { return 0; }

TEST_CASE("new delete") {
  CHECK(heap_sum() == 10); // 0+1+2+3+4 = 10
}

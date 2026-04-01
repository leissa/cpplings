#include <doctest/doctest.h>

// TODO: Fix compilation and test.
// Hint: references cannot be null.
int deref(int* p) {
    return *p;
}

TEST_CASE("deref works") {
    int x = 123;
    CHECK(deref(&x) == 123);
}

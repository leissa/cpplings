#include <doctest/doctest.h>

// TODO: Fix the return value.
int meaning_of_life() {
    return 0;
}

TEST_CASE("meaning of life") {
    CHECK(meaning_of_life() == 42);
}

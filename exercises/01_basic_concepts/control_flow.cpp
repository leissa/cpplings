#include <doctest/doctest.h>

// TODO: Use `continue` to skip negative numbers and `break` to stop
// at the first number greater than 100.
// Return the sum of all positive numbers <= 100.

int selective_sum() {
    int values[] = {5, -3, 20, -1, 50, 30, 150, 10};
    int sum = 0;
    for (int v : values) {
        sum += v;
    }
    return sum;
}

TEST_CASE("break vs continue") {
    CHECK(selective_sum() == 105);
}

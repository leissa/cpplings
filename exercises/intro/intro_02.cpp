#include <doctest/doctest.h>
#include <string>
#include <iostream>

int foo(int i, int j) {
    return i << j;
}

// TODO: Fix this function so the test passes.
std::string greet() {
    int i = 1;
    std::cout << foo(i, 33) << std::endl;
    return "hello";
}

TEST_CASE("greet returns correct string") {
    CHECK(greet() == "hello");
}

#include <doctest/doctest.h>
#include <string>

// TODO: Fix this function so the test passes.
std::string greet() {
    return "???";
}

TEST_CASE("greet returns correct string") {
    CHECK(greet() == "hello");
}

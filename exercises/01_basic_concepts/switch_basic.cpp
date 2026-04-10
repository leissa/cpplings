#include <doctest/doctest.h>

// TODO: Implement a function that returns a string for each color.
// Use a switch statement with an enum class.

enum class Light { RED, YELLOW, GREEN };

const char *light_action(Light l) { return ""; }

TEST_CASE("switch basic") {
  CHECK(light_action(Light::RED) == doctest::String("stop"));
  CHECK(light_action(Light::YELLOW) == doctest::String("caution"));
  CHECK(light_action(Light::GREEN) == doctest::String("go"));
}

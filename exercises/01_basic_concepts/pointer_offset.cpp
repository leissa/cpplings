#include <doctest/doctest.h>

// TODO: this function is supposed to return the number of bytes
// between two pointers. It misbehaves when end < start.
// Hint: check the slides for the right type for pointer differences.
uint8_t pointer_offset(uint8_t *start, uint8_t *end) { return end - start; }
TEST_CASE("pointer offset") {
  uint8_t buffer[10];
  CHECK(pointer_offset(buffer, buffer + 5) == 5);
  CHECK(pointer_offset(buffer + 5, buffer) == 0);
}

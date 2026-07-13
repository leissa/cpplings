// exercise: string_operations.cpp
#include <doctest/doctest.h>
#include <string>
#include <string_view>
#include <vector>

// TODO: Implement split(s, delimiter)
//   Takes a std::string_view and a char delimiter.
//   Returns a std::vector<std::string> of substrings between delimiters.
//   Example: split("a,b,c", ',') -> {"a", "b", "c"}
//   Hint: use std::string_view::find and std::string_view::substr.

std::vector<std::string> split(std::string_view s, char delimiter) {
  return {}; // TODO
}

// TODO: Implement increment_numbers(s)
//   Takes a std::string_view.
//   Finds the first contiguous sequence of digits in s,
//   increments it by 1, and returns the modified string.
//
std::string increment_number(std::string_view s) {
  return std::string(s); // TODO
}

// TODO: Implement file_extension(path)
//   Takes a std::string_view representing a file path.
//   Returns a std::string_view of the extension including the dot,
//   or an empty string_view if there is no extension.
//   Example: file_extension("photo.jpg") -> ".jpg"
//            file_extension("makefile")  -> ""
//   Hint: use std::string_view::rfind('.') and std::string_view::substr

std::string_view file_extension(std::string_view path) {
  return {}; // TODO
}

TEST_CASE("split") {
  CHECK(split("a,b,c", ',') == std::vector<std::string>{"a", "b", "c"});
  CHECK(split("one::two", ':') == std::vector<std::string>{"one", "", "two"});
  CHECK(split("alone", ',') == std::vector<std::string>{"alone"});
  CHECK(split("", ',') == std::vector<std::string>{""});
}

TEST_CASE("increment number in string") {
  CHECK(increment_number("file_007.txt") == "file_008.txt");
  CHECK(increment_number("version_9_final") == "version_10_final");
  CHECK(increment_number("no_digits") == "no_digits");
}

TEST_CASE("file extension") {
  CHECK(file_extension("photo.jpg") == ".jpg");
  CHECK(file_extension("archive.tar.gz") == ".gz");
  CHECK(file_extension("makefile") == "");
  CHECK(file_extension(".hidden") == ".hidden");
}

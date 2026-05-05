#include <algorithm>
#include <doctest/doctest.h>

// TODO: Define a struct `Student` with:
//   - const char* member `name`
//   - int member `grade`
//   - operator< that compares by grade (ascending)
//     Note: The operator< must be const.
//
// optional : add name comparison as a tie breaker.

struct Student {
  const char *name;
  int grade;
  // TODO: implement operator<
};

TEST_CASE("comparison operator sort") {
  Student students[] = {{"Alice", 85}, {"Bob", 92}, {"Carol", 78}};
  std::sort(students, students + 3);
  CHECK(students[0].grade == 78);
  CHECK(students[1].grade == 85);
  CHECK(students[2].grade == 92);
}

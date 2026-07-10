#include <doctest/doctest.h>
#include <mdspan>
#include <vector>

// TODO: Implement:
//
// trace(data, N)
//   Views 'data' as an NxN matrix using mdspan and returns the trace
//   (sum of diagonal elements: data[0,0] + data[1,1] + ... + data[N-1,N-1])
//
// transpose_copy(src_data, dst_data, rows, cols)
//   Views src as (rows x cols) and dst as (cols x rows).
//   Copies src[i,j] into dst[j,i] for all i,j.

double trace(double *data, int N) {
  return 0.0; // TODO: use std::mdspan with std::dextents<int, 2>{N, N}
}

void transpose_copy(const double *src, double *dst, int rows, int cols) {
  // TODO
}

TEST_CASE("mdspan trace") {
  // 3x3 identity
  double identity[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  CHECK(trace(identity, 3) == doctest::Approx(3.0));

  double m[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  CHECK(trace(m, 3) == doctest::Approx(15.0)); // 1+5+9
}

TEST_CASE("mdspan transpose") {
  // 2x3 source
  double src[] = {1, 2, 3, 4, 5, 6};
  double dst[6] = {};
  transpose_copy(src, dst, 2, 3);

  std::mdspan result{dst, std::dextents<int, 2>{3, 2}};
  CHECK(result[0, 0] == 1.0);
  CHECK(result[1, 0] == 2.0);
  CHECK(result[2, 0] == 3.0);
  CHECK(result[0, 1] == 4.0);
  CHECK(result[2, 1] == 6.0);
}

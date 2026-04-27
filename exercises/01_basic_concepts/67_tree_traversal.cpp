#include <doctest/doctest.h>

// TODO: Define a struct `Node` with:
//   - an int member called `value`
//   - a Node* member called `left` (default initialized to nullptr)
//   - a Node* member called `right` (default initialized to nullptr)

struct Node {};

// TODO: Implement find_max as a recursive lambda that takes a Node*
// and returns the maximum value in the tree.
// Use the self-passing pattern:
//   auto find_max = [](Node* node, auto self) -> int { ... };
//
// Hint: if a node has no children, its value is the max.
// Otherwise compare the node's value with the max of each subtree.

auto find_max = ? ;

TEST_CASE("lambda tree max") {
  //        5
  //       / \
  //      3   8
  //     /   / \
  //    7   2   1
  Node n7{7};
  Node n3{3, &n7, nullptr};
  Node n2{2};
  Node n1{1};
  Node n8{8, &n2, &n1};
  Node root{5, &n3, &n8};

  CHECK(find_max(&root, find_max) == 8);
  CHECK(find_max(&n3, find_max) == 7);
  CHECK(find_max(&n8, find_max) == 8);
  CHECK(find_max(&n7, find_max) == 7);
}

TEST_CASE("lambda tree max single node") {
  Node solo{42};
  CHECK(find_max(&solo, find_max) == 42);
}

TEST_CASE("lambda tree max left-only chain") {
  //    1
  //   /
  //  2
  // /
  // 9
  Node n9{9};
  Node n2{2, &n9, nullptr};
  Node n1{1, &n2, nullptr};

  CHECK(find_max(&n1, find_max) == 9);
}

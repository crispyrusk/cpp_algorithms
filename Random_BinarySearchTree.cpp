// to revise binary search tree
// shared_ptr - passed by reference and const reference. In this example, we never need to copy shared_ptr because ownership is never shared
// pre-order traversal of tree
#include <iostream>
#include <iterator>
#include <vector>
#include <memory>

using namespace std;

class Node {
public:
  int key;
  shared_ptr<Node> leftChild = nullptr;
  shared_ptr<Node> rightChild = nullptr;
  Node(const int keyArg) : key(keyArg) {}
};

class BinarySearchTree {
public:
  void insert(const int key);
  bool contains(const int key);
  void printPreOrder();
private:
  std::shared_ptr<Node> _root = nullptr;
  void _insertRecursively(shared_ptr<Node>& rootOfSubTree, const int key); // the rootOfSubTree holds the subtree where the new key is inserted
  bool _searchRecursively(const shared_ptr<Node>& rootOfSubTree, const int key);
  void _printPreOrder(shared_ptr<Node>& rootOfSubTree);
};


void BinarySearchTree::insert(const int key) {
  _insertRecursively(_root, key);
}

bool BinarySearchTree::contains(const int key) {
  return _searchRecursively(_root, key);
}

void BinarySearchTree::printPreOrder() {
  _printPreOrder(_root);
  std::cout << "\n";
}

void BinarySearchTree::_printPreOrder(shared_ptr<Node>& rootOfSubTree) {
  if (rootOfSubTree == nullptr) { return; }
  std::cout << rootOfSubTree->key << ", ";
  _printPreOrder(rootOfSubTree->leftChild);
  _printPreOrder(rootOfSubTree->rightChild);
}

void BinarySearchTree::_insertRecursively(shared_ptr<Node>& rootOfSubTree, const int key) {
  if (rootOfSubTree == nullptr) {
    rootOfSubTree = std::make_shared<Node>(key);
  }
  if (key < rootOfSubTree->key) {
    _insertRecursively(rootOfSubTree->leftChild, key);
  }
  else if (key > rootOfSubTree->key) {
    _insertRecursively(rootOfSubTree->rightChild, key);
  }
}

bool BinarySearchTree::_searchRecursively(const shared_ptr<Node>& rootOfSubTree, const int key) {
  if (rootOfSubTree == nullptr) {
    return false;
  }
  if (key < rootOfSubTree->key) {
    return _searchRecursively(rootOfSubTree->leftChild, key);
  }
  else if (key > rootOfSubTree->key) {
    return _searchRecursively(rootOfSubTree->rightChild, key);
  }
  else {
    return true;
  }
}

int main() {
  std::vector<int> inpSequence = { 10, 2, 3, 65, 3, 34, 5, 76, 3, 3, 2, 4, 6, 78, 8, 34, 3, 67 };
  BinarySearchTree bst;
  for (int i : inpSequence) {
    bst.insert(i);
    bst.printPreOrder();
  }
  for (int i : inpSequence) {
    cout << bst.contains(i) << "\n";
  }
  cout << bst.contains(1000) << "\n";
  return 0;
}

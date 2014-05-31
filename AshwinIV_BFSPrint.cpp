// write node keys one depth at a time

#include <iostream>
#include <iterator>
#include <vector>
#include <memory>
#include <queue>
#include <cassert>

using namespace std;
class Node {
public:
  int key = -1;
  std::shared_ptr<Node> rightChild = nullptr;
  std::shared_ptr<Node> leftChild = nullptr;
  Node(const int keyArg) : key(keyArg) { }
};

class Tree {
public:
  Tree(const std::string& tree);
  Tree();
  void printBfsOfTree();
private:
  std::shared_ptr<Node> root = nullptr;
};

Tree::Tree() {
  root = std::make_shared<Node>(1);
  root->leftChild = std::make_shared<Node>(2);
  root->rightChild = std::make_shared<Node>(3);
  root->leftChild->rightChild = std::make_shared<Node>(4);
  root->rightChild->leftChild = std::make_shared<Node>(5);
}

void Tree::printBfsOfTree() {
  queue<pair<shared_ptr<Node>, int> > q;
  int depth = 0;
  q.push(make_pair(root, 0));
  while (!q.empty()) {
    auto x = q.front();
    q.pop();
    auto const depthOfX = x.second;
    const shared_ptr<Node>& focusNode = x.first;
    if (focusNode == nullptr) { continue; }
    q.push(make_pair(focusNode->leftChild, depthOfX + 1));
    q.push(make_pair(focusNode->rightChild, depthOfX + 1));
    if (depthOfX > depth) {
      std::cout << std::endl;
      ++depth;
    }
    std::cout << focusNode->key << ",";
  }

}

int main() {
  Tree t;
  t.printBfsOfTree();
  return 0;
}
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

class LinkedList {
public:
  void appendToList(const std::string& keyArg);
  void printListInReverse();
  void removeDuplicates();
protected:
  class Node {
  public:
    std::shared_ptr<Node> prev = nullptr;
    const std::string key;
    Node(const std::string& keyArg) : key(keyArg) {}
  };
  std::shared_ptr<Node> tail = nullptr;
};

void LinkedList::appendToList(const std::string& keyArg) {
  auto newNode = std::make_shared<Node>(keyArg);
  newNode->prev = tail;
  tail = newNode;
}

void LinkedList::printListInReverse() {
  std::shared_ptr<Node> focusNode = tail;
  while (focusNode != nullptr) {
    std::cout << focusNode->key << " ";
    focusNode = focusNode->prev;
  }
  std::cout << "\n";
}

void LinkedList::removeDuplicates() {
  if (tail == nullptr) { return; }
  std::shared_ptr<Node> focusNode = tail->prev;
  std::shared_ptr<Node> focusNodeRunner = tail; // this is the runner trick which runs one element behind the focusNode
  std::unordered_map<std::string, bool> hashTable;
  hashTable[focusNodeRunner->key] = true;
  while (focusNode != nullptr) {
    if (hashTable.find(focusNode->key) != hashTable.end()) {
      focusNodeRunner->prev = focusNode->prev;
    }
    else {
      hashTable[focusNode->key] = true;
      focusNodeRunner = focusNodeRunner->prev;
    }
    focusNode = focusNode->prev;
  }
}

int main() {
  LinkedList ll;
  ll.appendToList("aaa");
  ll.appendToList("bbb");
  ll.appendToList("ccc");
  ll.appendToList("ddd");
  ll.appendToList("ccc");
  ll.appendToList("bbb");
  ll.printListInReverse();
  ll.removeDuplicates();
  ll.printListInReverse();
  return 0;
}
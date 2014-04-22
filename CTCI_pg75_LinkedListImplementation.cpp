#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

class LinkedList {
public:
  void appendToList(const std::string& keyArg);
  void printListInReverse();
  void deleteKey(const std::string& keyArg);
protected:
  class Node { 
  public:
    std::shared_ptr<Node> prev = nullptr;
    const std::string key;
    Node(const std::string& keyArg) :  key(keyArg) {}
  };
  std::shared_ptr<Node> tail = nullptr;
};

void LinkedList::appendToList(const std::string& keyArg) {
  //std::shared_ptr<Node> newNode = std::shared_ptr<Node>(new Node(keyArg));
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

void LinkedList::deleteKey(const std::string& keyArg) {
  if (tail != nullptr && tail->key == keyArg) {
    tail = tail->prev;
  }
  std::shared_ptr<Node> focusNode = tail;
  while (focusNode->prev != nullptr) {
    if (focusNode->prev->key == keyArg) {
      focusNode->prev = focusNode->prev->prev;
    }
    focusNode = focusNode->prev;
  }
}

int main() {
  LinkedList ll;
  ll.appendToList("aaa");
  ll.appendToList("bbb");
  ll.appendToList("ccc");
  ll.printListInReverse();
  ll.appendToList("ddd");
  ll.printListInReverse();
  ll.deleteKey("ccc");
  ll.printListInReverse();
  ll.deleteKey("ddd");
  ll.printListInReverse();
  return 0;
}
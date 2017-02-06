#include <iostream>
#include <memory>
#include <cassert>


using namespace std;

class Node
{
public:
    Node(const int dataArg) : data(dataArg)
    {
    }

    ~Node()
    {
        // for debugging
        //std::cout << "destroying node with data:" << data << std::endl;
    }

    int data = 0;
    shared_ptr<Node> next = nullptr;
};

class LinkedList
{
public:
    void insertNode(const int data)
    {
        shared_ptr<Node> newNode = shared_ptr<Node>(new Node(data));
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        auto walker = head;
        while (walker->next != nullptr)
        {
            walker = walker->next;
        }
        walker->next = newNode;
    }

    void deleteNode(const int data)
    {
        if (head == nullptr) { return; }
        auto walker = head;
        while (walker->next->data != data)
        {
            walker = walker->next;
        }
        walker->next = walker->next->next;
    }

    void printList()
    {
        auto walker = head;
        int index = 0;
        while (walker != nullptr)
        {
            std::cout << index++ << ": " << walker->data << std::endl;
            walker = walker->next;
        }
    }

private:
    shared_ptr<Node> head = nullptr;
};


void testFn1(){
    std::cout << "Test Fn 1" << std::endl;
    auto ll = LinkedList();
    ll.insertNode(10);
    ll.insertNode(20);
    ll.insertNode(30);
    ll.insertNode(50);
    ll.insertNode(60);
    ll.insertNode(40);
    ll.printList();
}


void testFn2(){
    std::cout << "Test Fn 2" << std::endl;
    auto ll = LinkedList();
    ll.insertNode(10);
    ll.insertNode(20);
    ll.insertNode(30);
    ll.insertNode(50);
    ll.insertNode(60);
    ll.insertNode(40);
    ll.printList();

    std::cout << "deleting node 50" << std::endl;
    ll.deleteNode(50);
    ll.printList();
}


int main(int argc, char** argv)
{
    testFn1();
    testFn2();
    return 0;
}
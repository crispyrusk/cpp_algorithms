///
/// Simple linked-list like implementation of stack
///

#include <iostream>
#include <memory>

using namespace std;

class Node
{
public:
    Node(const int dataArg) : data(dataArg)
    {
    }

    int data;
    shared_ptr<Node> next;
};


class Stack
{
public:
    void push(const int data)
    {
        auto newNode = shared_ptr<Node>(new Node(data));
        if (top == nullptr) {
            top = newNode;
            return;
        }
        newNode->next = top;
        top = newNode;
    }

    shared_ptr<Node> pop()
    {
        if (top == nullptr)
        {
            std::cout << "empty stack return 0" << std::endl;
            return nullptr;
        }
        auto rtrn = top;
        top = top->next;
        return rtrn;
    }

    void printStack()
    {
        auto walker = top;
        int index = 0;
        while (walker != nullptr)
        {
            std::cout << index++ << ": " << walker->data << std::endl;
            walker = walker->next;
        }
    }


private:
    shared_ptr<Node> top = nullptr;
};


void testFn1()
{
    std::cout << "Test Fn 1" << std::endl;
    auto s = Stack();
    s.push(10);
    s.push(20);
    s.push(15);
    s.printStack();
    
    auto popped = s.pop();
    while (popped != nullptr)
    {
        std::cout << popped->data << ", " ;
        popped = s.pop();
    }

}


int main(int argc, char** argv)
{
    testFn1();
    return 0;
}
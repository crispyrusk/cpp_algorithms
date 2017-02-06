///
/// Simple implementaion of queue using linked-list like data-struct
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


class Queue
{
public:
    void enqueue(const int data)
    {
        auto newNode = shared_ptr<Node>(new Node(data));
        if (last == nullptr)
        {
            first = newNode;
            last = newNode;
            return;
        }
        
        last->next = newNode;
        last = newNode;

    }

    shared_ptr<Node> dequeue()
    {
        if (first == nullptr)
        {
            return nullptr;
        }
        auto rtrn = first;
        first = first->next;
        return rtrn;
    }

    void printQueue()
    {
        int index = 0;
        auto walker = first;
        while (walker != nullptr)
        {
            std::cout << index++ << ": " << walker->data << std::endl;
            walker = walker->next;
        }
    }

private:
    shared_ptr<Node> first = nullptr;
    shared_ptr<Node> last = nullptr;

};


void testFn1()
{
    std::cout << "Test Fn 1" << std::endl;
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.printQueue();

    auto temp = q.dequeue();
    while (temp != nullptr)
    {
        std::cout << temp->data << ", ";
        temp = q.dequeue();
    }
    std::cout << std::endl;

}


int main(int argc, char** argv)
{
    testFn1();
    return 0;
}
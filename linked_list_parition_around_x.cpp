///
/// CTCI : Partition a linked list around a value x, such that all the nodes less than x come before and all nodes greater than x come after
/// Creating two tempory linked lists with lteq and gt; 
/// Solution is not complete; the lteq should be reversed
///

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

    shared_ptr<Node> getHead()
    {
        return head;
    }

    shared_ptr<Node> getTail()
    {
        if (head == nullptr)
        {
            return head;
        }

        auto walker = head;
        while (walker->next != nullptr)
        {
            walker = walker->next;
        }
        return walker;
    }

    void setHead(shared_ptr<Node> newHead)
    {
        head = newHead;
    }

private:
    shared_ptr<Node> head = nullptr;
};


class ParitionLinkedList
{
public:
    ParitionLinkedList(LinkedList& linkedList) : linkedList_(linkedList)
    {
    }

    void parition(const int partitionValue)
    {
        auto head = linkedList_.getHead();
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

        LinkedList ltEqLinkedList;
        LinkedList gtLinkedList;
        auto walker = head;
        while (walker != nullptr)
        {
            auto next = walker->next;
            walker->next = nullptr;
            if (walker->data <= partitionValue)
            {
                ltEqLinkedList.insertNode(walker->data);
            }
            else
            {
                gtLinkedList.insertNode(walker->data);
            }
            walker = next;
        }

        auto headOfLtEq = ltEqLinkedList.getHead();
        auto tailOfLtEq = ltEqLinkedList.getTail();
        auto headOfGt = gtLinkedList.getHead();

        if (headOfLtEq == nullptr)
        {
            linkedList_.setHead(headOfGt);
        }
        else if (headOfGt == nullptr)
        {
            linkedList_.setHead(headOfLtEq);
        }
        else
        {
            assert(tailOfLtEq != nullptr);
            assert(tailOfLtEq->next == nullptr);
            tailOfLtEq->next = headOfGt;
            linkedList_.setHead(headOfLtEq);
        }

    }

private:

    LinkedList& linkedList_;
    
};


void testFn1(){
    std::cout << "Test Fn 1" << std::endl;
    auto ll = LinkedList();
    ll.insertNode(110);
    ll.insertNode(30);
    ll.insertNode(40);
    ll.insertNode(5);
    ll.insertNode(19);
    ll.insertNode(40);
    ll.printList();

    std::cout << "parition" << std::endl;
    ParitionLinkedList(ll).parition(10);
    ll.printList();

}

void testFn2(){
    std::cout << "Test Fn 2" << std::endl;
    auto ll = LinkedList();
    ll.insertNode(5);
    ll.printList();

    std::cout << "parition" << std::endl;
    ParitionLinkedList(ll).parition(10);
    ll.printList();

}


void testFn3(){
    std::cout << "Test Fn 3" << std::endl;
    auto ll = LinkedList();
    ll.insertNode(10);
    ll.insertNode(9);
    ll.insertNode(8);
    ll.insertNode(7);
    ll.insertNode(6);
    ll.insertNode(5);
    ll.printList();

    std::cout << "parition" << std::endl;
    ParitionLinkedList(ll).parition(4);
    ll.printList();

}

void testFn4(){
    std::cout << "Test Fn 4" << std::endl;
    auto ll = LinkedList();
    ll.insertNode(10);
    ll.insertNode(9);
    ll.insertNode(8);
    ll.insertNode(7);
    ll.insertNode(6);
    ll.insertNode(5);
    ll.insertNode(4);
    ll.insertNode(3);
    ll.insertNode(2);

    ll.printList();

    std::cout << "parition" << std::endl;
    ParitionLinkedList(ll).parition(5);
    ll.printList();

}



int main(int argc, char** argv)
{
    testFn1();
    testFn2();
    testFn3();
    testFn4();


    return 0;
}
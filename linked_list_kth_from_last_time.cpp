// example code to illustrate the used of walker and runner - runner is ahead of the walker

#include <iostream>
#include <memory>

class Node
{
public:
    Node(const int data) : data(data) { }
    int data = 0;
    std::shared_ptr<Node> next = nullptr;
};

class LinkedList
{
public:
    
    void insertToList(const int i)
    {
        if (head == nullptr)
        {
            head = std::make_shared<Node>(i);
            return;
        }

        auto currNode = head;
        while (currNode->next != nullptr)
            currNode = currNode->next;

        currNode->next = std::make_shared<Node>(i);
    }


    void print() 
    {
        auto currNode = head;
        while (currNode != nullptr)
        {
            std::cout << currNode->data;
            currNode = currNode->next;
            if (currNode != nullptr)
                std::cout << ", ";
        }
    }

    std::shared_ptr<Node> head = nullptr;
};


std::shared_ptr<Node> getKthFromLast(std::shared_ptr<Node>& head, const unsigned int k)
{
    auto walker = head;
    auto runner = head;
    int counter = 0;
    while (runner != nullptr)
    {
        runner = runner->next;
        ++counter;
        if (counter > k)
            walker = walker->next;
    }

    return walker;

}

int main()
{
    LinkedList ll;
    for (unsigned int i = 0; i < 100; ++i)
        ll.insertToList(i);

    ll.print();
    std::cout << "\n";

    std::cout << "1 from last " << getKthFromLast(ll.head, 1)->data << std::endl;
    std::cout << "2 from last " << getKthFromLast(ll.head, 2)->data << std::endl;
    std::cout << "3 from last " << getKthFromLast(ll.head, 3)->data << std::endl;
    std::cout << "4 from last " << getKthFromLast(ll.head, 4)->data << std::endl;

    return 0;
}
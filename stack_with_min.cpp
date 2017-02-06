#include <iostream>
#include <memory>
#include <limits>
#include <cstdlib>

class Node
{
public:
    Node(const int dataArg, const int minBelow)
    {
        data = dataArg;
        minTillNow = (data < minBelow) ? data : minBelow;
    }

    int data = 0;
    int minTillNow = std::numeric_limits<int>::max();
    std::shared_ptr<Node> prev = nullptr;
};


class StackWithMin
{
public:

    void push(const int i)
    {
        if (top == nullptr)
        {
            top = std::make_shared<Node>(i, std::numeric_limits<int>::max());
        }
        else
        {
            auto newNode = std::make_shared<Node>(i, top->minTillNow);
            newNode->prev = top;
            top = newNode;
        }

    }

    std::shared_ptr<Node> pop()
    {
        if (top == nullptr)
            return top;
        else
        {
            auto currNode = top;
            top = top->prev;
            return currNode;
        }
    }

    int min()
    {
        if (top == nullptr)
            return std::numeric_limits<int>::max();
        return top->minTillNow;
    }

    void print()
    {
        auto currNode = top;
        while (currNode != nullptr)
        {
            std::cout << "(" << currNode->data << ", " << currNode->minTillNow << ")";
            currNode = currNode->prev;
            if (currNode != nullptr)
                std::cout << ", ";
        }
    }


    std::shared_ptr<Node> top = nullptr;

private:
    int minVal = std::numeric_limits<int>::max();
};


int main()
{
    StackWithMin stack;
    for (unsigned int i = 0; i < 100; ++i)
        stack.push(rand() % 100);

    stack.print();
    std::cout << "\n";

    std::cout << "The smallest of the stack " << stack.min() << std::endl;
    for (size_t i = 0; i < 200; ++i)
    {
        auto node = stack.pop();
        if (node)
            std::cout << "Popped " << node->data << std::endl;
        std::cout << "Min element on stack" << stack.min() << std::endl;
    }

    return 0;
}
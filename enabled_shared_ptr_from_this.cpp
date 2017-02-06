#include <iostream>
#include <unordered_map>
#include <memory>


class Node : public std::enable_shared_from_this<Node>
{
public:

    Node(const int i) : i_(i) { }

    std::shared_ptr<Node> insertToTail(const int i)
    {
        auto currNode = shared_from_this();
        while (currNode->next != nullptr)
            currNode = currNode->next;
        currNode->next = std::make_shared<Node>(i);
        return currNode->next;
    }

    void print()
    {
        auto currNode = shared_from_this();
        while (currNode != nullptr)
        {
            std::cout << currNode->i_;
            currNode = currNode->next;
            if (currNode != nullptr)
                std::cout << ", ";
        }
    }

protected:
    std::shared_ptr<Node> next = nullptr;
    int i_ = 0;
};



int main()
{
    auto root = std::make_shared<Node>(0);
    auto tail = root;
    for (int i = 1; i < 100; ++i)
        tail = tail->insertToTail(i);
    root->print();
    return 0;
}
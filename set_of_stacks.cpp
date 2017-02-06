///
/// CTCI: 3.3 Implementing a set of stacks (each stack has a bounded size
/// Using STL vectors
///

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class SetOfStacks
{   
public:

    SetOfStacks(const int stackLimitArg) : stackLimit_(stackLimitArg)
    {
    }

    void push(const int data)
    {
        if (setOfStacks_.empty())
        {
            setOfStacks_.push_back(vector<int>());
            setOfStacks_[0].push_back(data);
            return;
        }
        auto& lastStack = setOfStacks_.back();
        if (static_cast<int>(lastStack.size()) < stackLimit_) {
            lastStack.push_back(data);
        }
        else
        {
            setOfStacks_.push_back(vector<int>());
            setOfStacks_.back().push_back(data);
        }
    }

    int pop(const int data)
    {
        if (setOfStacks_.empty())
        {
            std::cout << "empty stack" << std::endl;
            return -1;
        }
        auto rtrn = setOfStacks_.back().back();
        setOfStacks_.back().pop_back();
        if (setOfStacks_.back().empty()) {
            setOfStacks_.pop_back();
        }
        return rtrn;
    }

    int popAt(int stackIndex)
    {
        if (stackIndex >= static_cast<int>(setOfStacks_.size()))
        {
            std::cout << "invalid index" << std::endl;
            return -1;
        }
        auto& stack = setOfStacks_[stackIndex];
        assert(stack.size() > 0);
        auto rtrn = stack.back();
        stack.pop_back();
        if (stack.empty())
        {
            setOfStacks_.erase(setOfStacks_.begin() + stackIndex);
        }
        return rtrn;
    }

    void printSs()
    {
        for (auto it1 = setOfStacks_.begin(); it1 != setOfStacks_.end(); ++it1)
        {
            for (auto it2 = it1->begin(); it2 != it1->end(); ++it2)
            {
                std::cout << *it2 << ", ";
            }
            std::cout << std::endl;
        }
    }

private:
    vector< vector<int> > setOfStacks_;
    const int stackLimit_;
};


void testFn1()
{
    std::cout << "Test Fn 1" << std::endl;
    auto ss = SetOfStacks(3);
    for (int i = 0; i < 9; ++i)
    {
        ss.push(i);
    }
    ss.printSs();

    for (int i = 0; i < 9; ++i)
    {
        ss.pop(i);
        ss.printSs();
    }

}

void testFn2()
{
    std::cout << "Test Fn 2" << std::endl;
    auto ss = SetOfStacks(3);
    for (int i = 0; i < 9; ++i)
    {
        ss.push(i);
    }
    ss.printSs();

    ss.popAt(1);
    ss.printSs();
    ss.popAt(1);
    ss.printSs();
    ss.popAt(1);
    ss.printSs();
    ss.popAt(1);
    ss.printSs();



}


int main(int argc, char** argv)
{
    testFn1();
    testFn2();
    return 0;
}
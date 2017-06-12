#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Heap 
{
public:
    
    vector<int> heap;

    void print()
    {
        for (auto& x : heap)
            std::cout << x << ", ";
        std::cout << std::endl;
    }

    void insert(int num)
    {
        heap.push_back(num);
        swim(heap.size() - 1);
    }

    int popMax()
    {
        assert(!heap.empty());
        int head = heap.front();
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        if (!heap.empty())
            sink(0);
        return head;
    }

    int swim(int index)
    {
        while (index>0)
        {
            int parent = index / 2;
            if (heap[index] < heap[parent])
                return index;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        return index;
    }

    int sink(int index)
    {
        while (index<heap.size())
        {
            int leftChildIndex = 2 * index + 1;
            int rightChildIndex = 2 * index + 2;
            if (rightChildIndex < heap.size() && leftChildIndex < heap.size())
            {
                // both children exist
                if (heap[index] < heap[rightChildIndex] || heap[index] < heap[leftChildIndex])
                {
                    // swap needed
                    auto indexToSwap = (heap[rightChildIndex] > heap[leftChildIndex]) ? rightChildIndex : leftChildIndex;
                    std::swap(heap[indexToSwap], heap[index]);
                    index = indexToSwap;
                    // continue in loop
                }
                else
                    return index; // swap not needed; return
            }
            else if (leftChildIndex < heap.size())
            {
                // only left child exists
                if (heap[index] < heap[leftChildIndex])
                {
                    // swap needed
                    std::swap(heap[leftChildIndex], heap[index]);
                    index = leftChildIndex;
                    // continue in loop
                }
                else
                    return index; // swap not needed; return
            }
            else
            {
                // neither children exist
                return index;
            }
        }
        return index;
    }

};

int main()
{
    auto h = Heap();
    h.insert(5);
    h.insert(10);
    h.insert(3);
    h.insert(100);
    h.insert(-10);
    h.insert(20);
    h.print();
    h.popMax();
    h.print();
    h.popMax();
    h.print();
    h.popMax();
    h.print();
    h.popMax();
    h.print();
    h.popMax();
    h.print();
    h.popMax();
    h.print();

    return 0;
}

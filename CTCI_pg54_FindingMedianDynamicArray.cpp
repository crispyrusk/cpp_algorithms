#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <cassert>


namespace {
  const size_t INVALID_INDEX = std::numeric_limits<size_t>::max();
}

template <typename T, typename Comp = std::less<T> >
class MyHeap {
public:
  void pop();
  void insert(const T t);
  T top() const;
  void print() const;
  size_t getSize() const;

private:
  std::vector<T> _heap;
  
  void _upheap(const size_t index);
  void _downheap(const size_t index);
  size_t _getLeftChildIndex(const size_t parentIndex) const;
  size_t _getRightChildIndex(const size_t parentIndex) const;
  size_t _getParentIndex(const size_t childIndex) const;
  size_t _getLastIndex() const;
};

template<typename T, typename Comp>
size_t MyHeap<T, Comp>::getSize() const {
  return _heap.size();
}

template<typename T, typename Comp>
size_t MyHeap<T, Comp>::_getLeftChildIndex(const size_t parentIndex) const {
  const size_t lastIndex = _getLastIndex();
  assert(lastIndex != INVALID_INDEX);
  assert(parentIndex <= lastIndex);
  const size_t leftChildIndex = 2*parentIndex + 1;
  return (leftChildIndex <= lastIndex) ? leftChildIndex : INVALID_INDEX;
}

template<typename T, typename Comp>
size_t MyHeap<T, Comp>::_getRightChildIndex(const size_t parentIndex) const {
  const size_t lastIndex = _getLastIndex();
  assert(lastIndex != INVALID_INDEX);
  assert(parentIndex <= lastIndex);
  const size_t rightChildIndex = 2*parentIndex + 2;
  return (rightChildIndex <= lastIndex) ? rightChildIndex : INVALID_INDEX;
}

template<typename T, typename Comp>
size_t MyHeap<T, Comp>::_getParentIndex(const size_t childIndex) const {
  const size_t lastIndex = _getLastIndex();
  assert(lastIndex != INVALID_INDEX);
  assert(childIndex <= lastIndex);
  assert(childIndex > 0);
  return (childIndex-1)/2;
}

template<typename T, typename Comp>
size_t MyHeap<T, Comp>::_getLastIndex() const {
  const size_t heapSize = _heap.size();
  return heapSize==0? INVALID_INDEX : heapSize-1;
}


template<typename T, typename Comp>
T MyHeap<T, Comp>::top() const {
  return _heap.front();
}

template<typename T, typename Comp>
void MyHeap<T, Comp>::insert(const T t) {
  _heap.push_back(t);
  const size_t lastIndex = _getLastIndex();
  assert(lastIndex != INVALID_INDEX);
  _upheap(lastIndex);
  print();
}

template<typename T, typename Comp>
void MyHeap<T, Comp>::pop() {
  const size_t lastIndex = _getLastIndex();
  assert(lastIndex != INVALID_INDEX);
  if(lastIndex > 0) {
    std::swap(_heap[0], _heap[lastIndex]);
  }
  const T rtrn = _heap.back();
  _heap.pop_back();
  _downheap(0);
  print();
}

template<typename T, typename Comp>
void MyHeap<T, Comp>::_downheap(const size_t index) {
  const size_t lastIndex = _getLastIndex();
  if( (index == INVALID_INDEX) || 
      (lastIndex == INVALID_INDEX) || 
      (index >= lastIndex) ) { 
    return;
  }
  const size_t leftChildIndex = _getLeftChildIndex(index);
  const size_t rightChildIndex = _getRightChildIndex(index);
  bool swapped = false;
  size_t swappedIndex = INVALID_INDEX;
  Comp comp = Comp();
  if( (leftChildIndex != INVALID_INDEX) && 
      ( comp(_heap[leftChildIndex], _heap[index]) ) ) {
        if ( (rightChildIndex != INVALID_INDEX) && 
             ( comp(_heap[rightChildIndex], _heap[leftChildIndex]) ) ) {
               std::swap(_heap[index], _heap[rightChildIndex]);
               swappedIndex = rightChildIndex;
        }
        else {
          std::swap(_heap[index], _heap[leftChildIndex]);  
          swappedIndex = leftChildIndex;
        }
        swapped = true;
  }
  else if ( (rightChildIndex != INVALID_INDEX) &&
            ( comp(_heap[rightChildIndex], _heap[index]) ) ) {
              std::swap(_heap[index], _heap[rightChildIndex]);
              swappedIndex = rightChildIndex;
              swapped = true;
  }
  if (swapped) {
    assert(swappedIndex != INVALID_INDEX);
    _downheap(swappedIndex);
  }

}

template<typename T, typename Comp>
void MyHeap<T, Comp>::_upheap(const size_t index) {
  const size_t lastIndex = _getLastIndex();
  if( (index == INVALID_INDEX) ||
      (lastIndex == INVALID_INDEX) ||
      (index == 0) ) {
        return ;
  }
  assert(index <= lastIndex);
  const size_t parentIndex = _getParentIndex(index);
  Comp comp = Comp();
  if ( comp(_heap[index], _heap[parentIndex]) ) {
    std::swap(_heap[index], _heap[parentIndex]);
    _upheap(parentIndex);
  }
}

template<typename T, typename Comp>
void MyHeap<T, Comp>::print() const {
  std::copy(_heap.begin(), _heap.end(), std::ostream_iterator<T>(std::cout, " "));
  std::cout << std::endl;
}


void testMinMaxHeaps() {
  MyHeap<int> minHeap;
  MyHeap<int, std::greater<int> > maxHeap;
  int arr[10] = {5,6,4,3,2,7,8,1,2,9};
  std::vector<int> v(arr, arr+10);

  for(int x : v) {
    minHeap.insert(x);
  }
  while (minHeap.getSize()) {
    minHeap.pop();
  }

  for(int x : v) {
    maxHeap.insert(x);
  }
  while (maxHeap.getSize()) {
    maxHeap.pop();
  }
}

template<typename T>
void insertToMaxOrMinHeaps(const T x, 
                           MyHeap<T>& bottomHalfOfArrInMinHeap, 
                           MyHeap<T, std::greater<T> >& topHalfOfArrInMaxHeap) 
{
  if(bottomHalfOfArrInMinHeap.getSize()>0 && topHalfOfArrInMaxHeap.getSize()>0) {
      if(x>=bottomHalfOfArrInMinHeap.top()) {
        bottomHalfOfArrInMinHeap.insert(x);
      }
      else {
        topHalfOfArrInMaxHeap.insert(x);
      }
    }
    else if(bottomHalfOfArrInMinHeap.getSize()==0 && topHalfOfArrInMaxHeap.getSize()>0) {
      if(x <= topHalfOfArrInMaxHeap.top() ) {
        topHalfOfArrInMaxHeap.insert(x);
      }
      else {
        bottomHalfOfArrInMinHeap.insert(x);
      }
    }
    else if(bottomHalfOfArrInMinHeap.getSize()>0 && topHalfOfArrInMaxHeap.getSize()==0) {
      if(x >=  bottomHalfOfArrInMinHeap.top()) {
        bottomHalfOfArrInMinHeap.insert(x);
      }
      else {
        topHalfOfArrInMaxHeap.insert(x);
      }
    }
    else {
      bottomHalfOfArrInMinHeap.insert(x);
    }

}

template<typename T>
void rebalance(MyHeap<T>& bottomHalfOfArrInMinHeap, 
               MyHeap<T, std::greater<T> >& topHalfOfArrInMaxHeap) 
{
  const size_t sizeOfBottom = bottomHalfOfArrInMinHeap.getSize();
  const size_t sizeOfTop = topHalfOfArrInMaxHeap.getSize();
  const size_t meanSize = (sizeOfBottom+sizeOfTop)/2;
  if (meanSize==0) { 
    return;
  }
  if (sizeOfBottom>meanSize && sizeOfTop<meanSize) {
    const T x = bottomHalfOfArrInMinHeap.top();
	bottomHalfOfArrInMinHeap.pop();
    topHalfOfArrInMaxHeap.insert(x);
  }
  else if (sizeOfTop>meanSize && sizeOfBottom<meanSize) {
    const T x = topHalfOfArrInMaxHeap.top();
	topHalfOfArrInMaxHeap.pop();
    bottomHalfOfArrInMinHeap.insert(x);
  }
}


int mainMedianUsingHeaps() {
  const int N = 9;
  int arr[N] = {10,9,4,3,2,7,8,1,9};
  std::vector<int> v(arr, arr + N);
  MyHeap<int> bottomHalfOfArrInMinHeap;
  MyHeap<int, std::greater<int> > topHalfOfArrInMaxHeap;
  for (int x: v ) {
    insertToMaxOrMinHeaps(x, bottomHalfOfArrInMinHeap, topHalfOfArrInMaxHeap);
    rebalance(bottomHalfOfArrInMinHeap, topHalfOfArrInMaxHeap);
  }
  double median = 0;
  assert(bottomHalfOfArrInMinHeap.top()>=topHalfOfArrInMaxHeap.top());
  if (bottomHalfOfArrInMinHeap.getSize() > topHalfOfArrInMaxHeap.getSize()) {
	  assert(bottomHalfOfArrInMinHeap.getSize() - topHalfOfArrInMaxHeap.getSize() <= 1);
	  median = bottomHalfOfArrInMinHeap.top();
  }
  else if (topHalfOfArrInMaxHeap.getSize() > bottomHalfOfArrInMinHeap.getSize()) {
	  assert(topHalfOfArrInMaxHeap.getSize() - bottomHalfOfArrInMinHeap.getSize() <= 1);
	  median = topHalfOfArrInMaxHeap.top();
  }
  else {
	  median = static_cast<double>(bottomHalfOfArrInMinHeap.top() + topHalfOfArrInMaxHeap.top());
	  median /= 2.0;
  }
  std::cout << "median:" << median << std::endl;
  return 0;
}

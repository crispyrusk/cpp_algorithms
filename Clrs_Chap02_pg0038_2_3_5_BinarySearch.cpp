// CLRS Chapter 2 - Excercise 2.3-5
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cassert>

std::size_t getIndexByBinarySearch(std::vector<int>::iterator itBegin,
                                   std::vector<int>::iterator itEnd, 
                                   int search) {
  assert(std::is_sorted(itBegin, itEnd));
  std::vector<int>::iterator itBeginMover = itBegin;
  std::vector<int>::iterator itEndMover = itEnd;
  while(itBeginMover<itEndMover) {
    auto itMidPt = itBeginMover + (std::distance(itBeginMover, itEndMover))/2;
    assert(itMidPt < itEndMover);
    if(search == *itMidPt) {
      return std::distance(itBegin, itMidPt);
    }
    else if (search < *itMidPt) {
      itEndMover = itMidPt;
    }
    else {
      itBeginMover = itMidPt+1;
    }
  }
  return std::distance(itBegin, itEnd);
}

std::size_t getIndexByBinarySearch(std::vector<int>& v, int search) {
  return getIndexByBinarySearch(v.begin(), v.end(), search);
}

int mainBinarySeach() {
  int a[10] = {1,2,3,4,5,6,7,8,9,10};
  std::vector<int> v(a, a+10);
  std::cout << 
    getIndexByBinarySearch(v, 0) << " " << 
    getIndexByBinarySearch(v, 1) << " " << 
    getIndexByBinarySearch(v, 2) << " " << 
    getIndexByBinarySearch(v, 3) << " " << 
    getIndexByBinarySearch(v, 4) << " " << 
    getIndexByBinarySearch(v, 5) << " " << 
    getIndexByBinarySearch(v, 6) << " " << 
    getIndexByBinarySearch(v, 10) << " " << 
    getIndexByBinarySearch(v, 11) << " " << 

    "";

  return 0;
}
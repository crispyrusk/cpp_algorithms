// 20140227
// quick sort, using Dijkstra's 3 way partitioning
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


// invariant
// quicksort has three iterators for three way paritioning
// [itBegin, itLt) contains less than pivot
// [itLt, itMover) contains == pivot
// [itGt, itEnd) contains > pivot
void quickSort(std::vector<int>::iterator itBegin, std::vector<int>::iterator itEnd) {
  if (itBegin == itEnd) { return; }
  std::vector<int>::iterator itLt = itBegin; 
  std::vector<int>::iterator itMover = itBegin;
  std::vector<int>::iterator itGt = itEnd; 
  const int pivot = *itMover;
  ++itMover;
  while (itMover != itGt) {
    if (*itMover < pivot) {
      std::swap(*itMover, *(itLt++));
      ++itMover;
    }
    else if (*itMover > pivot) {
      std::swap(*itMover, *(--itGt));
    }
    else {
      ++itMover;
    }
  }
  quickSort(itBegin, itLt);
  quickSort(itGt, itEnd);
}

int main() {
  std::vector<int> inp = { 2, 4, 5, 6, 7, 3, 2, 1, 2, 4, 6, 7, 8, 1, 3, 6, 9, 3, 2, 4, 6 };
  std::copy(inp.begin(), inp.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  std::random_shuffle(inp.begin(), inp.end());
  quickSort(inp.begin(), inp.end());
  std::copy(inp.begin(), inp.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  return 0;
}
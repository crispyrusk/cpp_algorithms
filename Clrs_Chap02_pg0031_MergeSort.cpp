// CLRS Chapter 2 pp 31
#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>


void merge(std::vector<int>::iterator itBegin,
           std::vector<int>::iterator itMidPt,
           std::vector<int>::iterator itEnd,
           std::vector<int>& v_aux)
{
  //assert(isSorted(itBegin, itMidPt);
  //assert(isSorted(itMidPt, itEnd);
  std::size_t numElementsToSort = std::distance(itBegin, itEnd);
  assert(v_aux.size() >= numElementsToSort);
  auto itBeginMover = itBegin; // serves the purpose of sentinel (CLRS) to avoid spillover
  auto itMidPtMover = itMidPt;
  for(std::size_t i = 0; i <numElementsToSort; ++i) {
    // remember to check guard: to avoid spilling into Right Child during Merge
    if( !(itMidPtMover < itEnd) || 
        ((itBeginMover < itMidPt) && 
         (*itBeginMover < *itMidPtMover)) )
    {
      v_aux[i] = *(itBeginMover++);
    }
    else {
      v_aux[i] = *(itMidPtMover++);
    }
    assert(itBeginMover<=itMidPt);
    assert(itMidPtMover<=itEnd);
  }
  std::copy(v_aux.begin(), v_aux.begin()+numElementsToSort, itBegin);
}

void mergeSort(std::vector<int>::iterator itBegin, 
               std::vector<int>::iterator itEnd,
               std::vector<int>& v_aux) 
{
  std::size_t numElementsToSort = std::distance(itBegin, itEnd);
  if(numElementsToSort==1) {
    return;
  }
  auto itMidPt = itBegin + numElementsToSort/2;
  mergeSort(itBegin, itMidPt, v_aux);
  mergeSort(itMidPt, itEnd, v_aux);
  merge(itBegin, itMidPt, itEnd, v_aux);
}

int mainMergeSort() {
  int arr[10] = {10,8,9,5,3,2,1,6,7,4};
  std::vector<int> v(arr, arr+10);
  std::vector<int> v_aux(v.size());
  mergeSort(v.begin(), v.end(), v_aux);
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  return 0;
}
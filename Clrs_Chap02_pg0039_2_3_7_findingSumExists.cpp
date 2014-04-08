#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cassert>

std::size_t getIndexByBinarySearch(std::vector<int>::iterator itBegin,
                                   std::vector<int>::iterator itEnd, 
                                   int search); // from BinarySearch


int mainFindPairToSum() {
  int a[10] = {1,2,-3,4,5,6,7,-8,9,-10};
  std::vector<int> v(a, a+10);
  int sum = 10; // 5;
  std::sort(v.begin(), v.end());
  bool foundSum = false;
  for(auto it = v.begin(); it != v.end(); ++it) {
    int complement = sum - *it;
    auto index = getIndexByBinarySearch(it+1, v.end(), complement);
    if(index < std::distance(it+1, v.end())) {
      assert(*(it+1+index) == complement);
      foundSum = true;
      break;
    }
  }
  std::cout << foundSum << std::endl;
  return 0;
}
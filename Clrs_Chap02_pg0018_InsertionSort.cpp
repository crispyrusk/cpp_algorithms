#include <iostream>
#include <vector>
#include <iterator>

// main idea is to create gaps for insertion 
// and move the gap sequentially to the front of the array

int mainInsertionSort() {
  int a[4]={4,3,1,2};
  std::vector<int> v(a, a+4);
  for(unsigned int keyPos=1; keyPos < v.size(); ++keyPos) {
    int key = v[keyPos];
    int insertPos = keyPos-1;
    while(insertPos >= 0 && key < v[insertPos]) {
      v[insertPos+1] = v[insertPos]; // create a gap at insertPos
      --insertPos;
    }
      v[insertPos+1] = key; // push key into gap
  }
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout));
  return 0;
}
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>


int main() {
  std::vector<int> a(10);
  std::vector<int> b(5);
  std::srand(std::time(0));
  for (int i = 0; i < 5; ++i) {
    a[i] = std::rand() % 100;
    b[i] = std::rand() % 100;
  }
  std::sort(a.begin(), a.begin() + 5);
  std::sort(b.begin(), b.begin() + 5);
  std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << "\n";
  std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << "\n";
  std::vector<int>::reverse_iterator ritMover = a.rbegin();
  std::vector<int>::reverse_iterator ritA = a.rbegin() + 5;
  std::vector<int>::reverse_iterator ritB = b.rbegin();
  while (ritMover != a.rend()) {
    if ( 
      (ritA != a.rend() && ritB != b.rend() && (*ritA >= *ritB)) 
      || (ritB == b.rend()) 
      ) {
      *(ritMover++) = *(ritA++);
    }
    else {
      assert(ritB != b.rend());
      *(ritMover++)= *(ritB++);
    }
  }
  std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << "\n";
  std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, ","));
  std::cout << "\n";
  return 0;
}
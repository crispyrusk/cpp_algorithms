// Knuth's algorithm to randomly select M integers from N without replacement
// logic assume that M = 2 and N = 5
// we tranverse from i = 0 to N-1, and select a random i till we fill up M places
// when we are at positin i, the remaining numbers are N-i, and let us assume that we have filled up j places (remaininngToSelect = M - j)
//                           we need to select remainingToSelect from N-i places, so the probab of choosing i is remainingToSelect/(N-i). One way realize this 
//                           rand()%(N-i) <  remainingToSelect (we generate, r, at random from 0 to N-i and select true if r < remainingToSelect)


#include <iostream>
#include <random>
#include <ctime>

int main() {
  const int N = 100;
  const int M = 10;
  srand(time(0));
  int remainingToSelect = M;
  for (int i = 0; i < N; ++i){
    if (rand() % (N - i) < remainingToSelect) {
      std::cout << i << ", ";
      --remainingToSelect;
      if (remainingToSelect == 0) { break; }
    }
  }
  return 0;
}
// using std::bitset
// remember: no shortcut operators for bitwise operators
// findNextGreaterNumberWithSameNumberOfOnes, SWAP LSB first one with a first zero after 1, and push remaining ones before prev first one towards LSB as xyz...1111..111 (example - 110 0 11 -> 110 1 10 -> 110 1 01) 
// findPrevSmallerNumberWithSameNumberOfOnes, SWAP LSB first zero with first one after the 0, and push the remaining ones towards the old one's posistion , ie. ,xyz...01111 (example - 1 1 0 0 11 --> 1 0 0 1 11 --> 1 0 1110)
#include <iostream>
#include <iterator>
#include <bitset>
#include <cassert>
#include <ctime>
#include <cstdlib>

void insertNToMAtGivenPos(const unsigned int M, unsigned int& N, const unsigned int i, const unsigned int j) {
  assert( N >= ((1 << (j +1  - i))<< i) );
  N = N & (~(1 << (j + 1 - i))) << i;
  N = N | (M << i);
}

unsigned int findNextGreaterNumberWithSameNumberOfOnes(unsigned int N) {
  assert(N > 0);
  unsigned int index = 0;
  unsigned int nextN = N;
  unsigned int lowest1Pos = -1;
  unsigned int lowest0After1Pos = -1;
  while (1) {
    unsigned int temp = N & (1 << index);
    if (lowest1Pos == -1) {
      if (temp > 0) { lowest1Pos = index; }
    }
    else if (lowest0After1Pos == -1 ) { 
      if (temp == 0) { lowest0After1Pos = index; }
    }
    else  {
      break;
    }
    ++index;
  }
  nextN = nextN & ~(1 << lowest1Pos);
  nextN = nextN | (1 << lowest0After1Pos);
  const unsigned int lsbLowerThanSwapped1Pos = nextN & ((1 << lowest0After1Pos) - 1);
  nextN = nextN & (~((1 << lowest0After1Pos) - 1));
  nextN = nextN | ((1 << std::bitset<32>(lsbLowerThanSwapped1Pos).count()) - 1);

  unsigned int testNextN = N;
  while (std::bitset<32>(++testNextN).count() != std::bitset<32>(N).count());
  std::cout << std::bitset<16>(N) << ", " << std::bitset<16>(nextN) << ", bruteForce" << std::bitset<16>(testNextN) << "\n";
  std::cout << N << ", " << nextN << ", bruteForce" << testNextN << "\n";
  assert(nextN == testNextN);
  return nextN;
}

unsigned int findPrevSmallerNumberWithSameNumberOfOnes(unsigned int N) {
  assert(N > 0);
  unsigned int index = 0;
  unsigned int prevN = N;
  unsigned int lowest0Pos = -1;
  unsigned int lowest1After0Pos = -1;
  while (1) {
    unsigned int temp = N & (1 << index);
    if (lowest0Pos == -1) {
      if (temp == 0) { lowest0Pos = index; }
    }
    else if (lowest1After0Pos == -1) {
      if (temp > 0) { lowest1After0Pos = index; }
    }
    else  {
      break;
    }
    ++index;
  }
  prevN = prevN | (1 << lowest0Pos);
  prevN = prevN & (~(1 << lowest1After0Pos));
  const unsigned int lowerThanOldSwapped1Pos = prevN & ((1 << lowest1After0Pos) - 1);
  prevN = prevN & ~((1 << lowest1After0Pos) - 1);
  const unsigned int numOnes = std::bitset<32>(lowerThanOldSwapped1Pos).count();
  prevN = prevN | (((1 << numOnes) - 1) << (lowest1After0Pos - numOnes));
  unsigned int testPrevN = N;
  while (std::bitset<32>(--testPrevN).count() != std::bitset<32>(N).count());
  std::cout << std::bitset<16>(N) << ", " << std::bitset<16>(prevN) << ", bruteForce:" << std::bitset<16>(testPrevN) << "\n";
  std::cout << N << ", " << prevN << ", bruteForce:" << testPrevN << "\n";
  assert(prevN == testPrevN);
  return prevN;
}


unsigned int main() {
  unsigned int N = 0x600;
  unsigned int M = 0x13;
  std::cout << "M = " << std::bitset<16>(M) << ", N = " << std::bitset<16>(N) << std::endl;
  insertNToMAtGivenPos(M, N, 2, 6);
  std::cout << "M = " << std::bitset<16>(M) << ", N = " << std::bitset<16>(N) << std::endl;
  srand(std::time(0));
  for (unsigned int i = 0; i < 100; ++i) {
    unsigned int NN = std::rand();
    unsigned int NN_next = findNextGreaterNumberWithSameNumberOfOnes(NN);
    unsigned int NN_prev = findPrevSmallerNumberWithSameNumberOfOnes(NN);
  }
  return 0;
}
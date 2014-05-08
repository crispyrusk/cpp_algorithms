// using std::bitset
// remember: no shortcut operators for bitwise operators
#include <iostream>
#include <iterator>
#include <bitset>
#include <cassert>
#include <ctime>
#include <cstdlib>

void insertNToMAtGivenPos(const int M, int& N, const int i, const int j) {
  assert( N >= ((1 << (j +1  - i))<< i) );
  N = N & (~(1 << (j + 1 - i))) << i;
  N = N | (M << i);
}

int findGreaterNumberWithSameNumberOfOnes(int N) {
  assert(N > 0);
  N = 12;
  int index = 0;
  int nextN = N;
  int lowest1Pos = -1;
  int lowest0After1Pos = -1;
  while (1) {
    int temp = N & (1 << index);
    if (lowest1Pos == -1) {
      if (temp > 1) { lowest1Pos = index; }
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
  int testNextN = N + 1;
  while (std::bitset<32>(++testNextN).count() != std::bitset<32>(N).count());
  std::cout << std::bitset<16>(N) << ", " << std::bitset<16>(nextN) << ", bruteForce" << std::bitset<16>(testNextN) << "\n";
  std::cout << N << ", " << nextN << ", bruteForce" << testNextN << "\n";
  assert(nextN == testNextN);
  return nextN;
}


int main() {
  int N = 0x600;
  int M = 0x13;
  std::cout << "M = " << std::bitset<16>(M) << ", N = " << std::bitset<16>(N) << std::endl;
  insertNToMAtGivenPos(M, N, 2, 6);
  std::cout << "M = " << std::bitset<16>(M) << ", N = " << std::bitset<16>(N) << std::endl;
  srand(std::time(0));
  for (int i = 0; i < 100; ++i) {
    int NN = std::rand();
    int NN_next = findGreaterNumberWithSameNumberOfOnes(NN);
  }
  return 0;
}
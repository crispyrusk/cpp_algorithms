// using chrono api to measure time
// dynamic programming from CS folks perspective - caching computed results to reuse in the context of distributive law
// dp_cache - dynamic programming cache
#include <iostream>
#include <iterator>
#include <chrono>
#include <vector>
#include <cassert>
#include <Windows.h>



int numPossibleJumps(const int n) {
  assert(n >= 0);
  if (n <= 3) { return n; }
  return (1 + numPossibleJumps(n - 1) +
    2 + numPossibleJumps(n - 2) +
    3 + numPossibleJumps(n - 3));
}

int numPossibleJumpsWithDpCache(const int n, std::vector<int>& jumpsCache) {
  assert(n >= 0);
  if (n <= 3) { return n; }
  if (jumpsCache[n] >= 0) { return jumpsCache[n]; }
  jumpsCache[n] = (1 + numPossibleJumpsWithDpCache(n - 1, jumpsCache) +
    2 + numPossibleJumpsWithDpCache(n - 2, jumpsCache) +
    3 + numPossibleJumpsWithDpCache(n - 3, jumpsCache));
  return jumpsCache[n];
}

using namespace std::chrono;
void printTimeElapsed(const high_resolution_clock::time_point& tic, const high_resolution_clock::time_point& toc) {
  std::cout << "elapsed time: " << duration_cast<milliseconds>(toc - tic).count() <<  " ms" << std::endl;
}

int main() {
  auto tic = high_resolution_clock::now();
  std::cout << "3: " << numPossibleJumps(3) << std::endl;
  auto toc = high_resolution_clock::now();
  printTimeElapsed(tic, toc);

  const int N = 40;

  tic = high_resolution_clock::now();
  std::cout << N <<": " << numPossibleJumps(N) << std::endl;
  toc = high_resolution_clock::now();
  printTimeElapsed(tic, toc);

  std::vector<int> jumpsCache(N+1, -1);
  tic = high_resolution_clock::now();
  std::cout << N << ": " << numPossibleJumpsWithDpCache(N, jumpsCache) << std::endl;
  toc = high_resolution_clock::now();
  printTimeElapsed(tic, toc);


  return 0;
}
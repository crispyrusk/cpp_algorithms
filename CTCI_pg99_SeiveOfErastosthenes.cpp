#include <iostream>
#include <iterator>
#include <vector>
#include <cassert>

int findNextPrime(const int prime, std::vector<bool>& primeFlags) {
  assert(primeFlags.size() > 1);
  for (std::size_t idx = prime; idx < primeFlags.size(); ++idx) {
    if (primeFlags[idx] == true) {
      return idx + 1;
    }
  }
  return -1;
}

void markAllMultiplesFalse(const int prime, std::vector<bool>& primeFlags) {
  assert(primeFlags.size()> 1);
  for (std::size_t idx = 2*prime-1; idx < primeFlags.size(); idx += prime) {
    primeFlags[idx] = false;
  }
}

void computePrimes(std::vector<int>& primes, std::vector<bool>& primeFlags) {
  assert(primeFlags.size() > 1);
  for (std::size_t idx = 1; idx <= primeFlags.size(); ++idx) {
    const int nextPrime = findNextPrime(primes.back(), primeFlags);
    if (nextPrime < 0) {
      return;
    }
    primes.push_back(nextPrime);
    markAllMultiplesFalse(nextPrime, primeFlags);
  }
}

int main() {
  const int MAX_NUM = 100;
  std::vector<bool> primeFlags(MAX_NUM, true);
  std::vector<int> primes;
  primes.push_back(1);
  computePrimes(primes, primeFlags);
  std::copy(primes.begin(), primes.end(), std::ostream_iterator<int>(std::cout, ", "));
  return 0;
}
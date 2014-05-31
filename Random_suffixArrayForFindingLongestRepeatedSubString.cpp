#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>


bool isSmallerThan(std::string::const_iterator itLhs, std::string::const_iterator itRhs, std::string::const_iterator itEnd) {
  for (; itLhs != itEnd && itRhs != itEnd; ++itLhs, ++itRhs) {
    if (*itLhs < *itRhs) {
      return true;
    }
    else if (*itRhs < *itLhs) {
      return false;
    }
  }
  return false;
}

int getSizeOfLongestPrefix(std::string::const_iterator itFirst, std::string::const_iterator itSecond, std::string::const_iterator itEnd) {
  int rtrn = 0;
  for (; itFirst != itEnd && itSecond != itEnd; ++itFirst, ++itSecond) {
    if (*itFirst == *itSecond) {
      ++rtrn;
    }
    else {
      return rtrn;
    }
  }
  return rtrn;
}

void printStringFromIndex(const std::string& s, const int index) {
  assert(index < s.size());
  for (auto it = s.begin() + index; it != s.end(); ++it) {
    std::cout << *it;
  }
}

int main() {
  std::string s("ask not what your country can do for you, but what you can do for your country");
  std::vector<int> indices(s.size());
  std::iota(indices.begin(), indices.end(), 0);
  std::sort(indices.begin(), indices.end(), 
    [&s](const int indexLhs, const int indexRhs){return isSmallerThan(s.begin() + indexLhs, s.begin() + indexRhs, s.end()); });
  for (std::size_t i = 0; i < indices.size(); ++i) {
    const int idx = indices[i];
    std::cout << "idx=" << idx << ": ";
    if (i > 0) {
      std::cout << "pmatch: " << getSizeOfLongestPrefix(s.begin() + idx, s.begin() + indices[i - 1], s.end()) << ": ";
    }
    printStringFromIndex(s, idx);
    std::cout << std::endl;
  }
  return 0;
}

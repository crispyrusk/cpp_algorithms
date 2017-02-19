#include <iostream>
#include <iterator>
#include <string>
#include <cassert>

namespace {
  const int maxLenOfStringRange = 10;   // convention is that each swap machine can operate on  2*maxLenOfStringRange
}

void swapPairOfRanges(std::string::iterator leftItBegin, std::string::iterator leftItEnd, std::string::iterator rightItBegin, std::string::iterator rightItEnd) {
  assert((leftItEnd - leftItBegin) == (rightItEnd - rightItBegin));
  for (int i = 0; i < leftItEnd - leftItBegin; ++i) {
    std::swap(*(leftItBegin + i), *(rightItEnd - 1 - i));
  }
}

void swapSingleRange(std::string::iterator itBegin, std::string::iterator itEnd) {
  assert(itBegin < itEnd);
  while (itBegin < (itEnd-1)) {
    std::swap(*itBegin, *(itEnd - 1));
    ++itBegin;
    --itEnd;
  }
}

void swapRecursively(std::string::iterator itBegin, std::string::iterator itEnd) {
  assert(itBegin <= itEnd);
  if (itEnd - itBegin == 1) { return; }
  std::string::iterator leftItEnd = itBegin + maxLenOfStringRange;
  std::string::iterator rightItBegin = itEnd - maxLenOfStringRange;
  if (leftItEnd <= rightItBegin) {
    swapPairOfRanges(itBegin, leftItEnd, rightItBegin, itEnd);
    swapRecursively(leftItEnd, rightItBegin);
  }
  else {
    assert(itEnd - itBegin <= 2 * maxLenOfStringRange);
    swapSingleRange(itBegin, itEnd);
  }
}

int main() {
  std::string longString("this is a very long string for the sake of arguement");
  swapRecursively(longString.begin(), longString.end());
  std::cout << longString << std::endl;
  return 0;
}
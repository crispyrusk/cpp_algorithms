#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

// O(N) algorithm to find max sub-array
// trick - hint from CLRS:
// Method of induction - start from left and find the max of array[0..N-1]. Keep increasing N 
// maxSubArray(array[0..N]) = maxSubArray(array[0..N-1], array[j..N]), where array[j..N] is a trailing subarray containing N. 
// we need to convince ourselves that a[j..N] is a the maximum non-negative subarray containing N - this was the hard part
void findMaxSubArray(const vector<int>::iterator& inpSeqBegin, const vector<int>::iterator& inpSeqEnd,
  vector<int>::iterator& itMaxSubArrayBegin, vector<int>::iterator& itMaxSubArrayEnd, int& maxSubArraySum)
{
  vector<int>::iterator movingEndIt = inpSeqBegin;
  vector<int>::iterator itMaxNonNegTrailingSubArrayBegin = inpSeqBegin;
  vector<int>::iterator itMaxNonNegTrailingSubArrayEnd = inpSeqBegin;
  int maxNonNegTrailingSubArraySum = 0;
  while (movingEndIt != inpSeqEnd) {
    ++movingEndIt;
    itMaxNonNegTrailingSubArrayEnd = movingEndIt;
    const int trailingSubArraySum = accumulate(itMaxNonNegTrailingSubArrayBegin, itMaxNonNegTrailingSubArrayEnd, 0); // calc looks wasteful, but okay for now
    if (trailingSubArraySum > maxSubArraySum) {
      maxSubArraySum = trailingSubArraySum;
      itMaxSubArrayBegin = itMaxNonNegTrailingSubArrayBegin;
      itMaxSubArrayEnd = itMaxNonNegTrailingSubArrayEnd;
    }
    if (trailingSubArraySum < 0) {
      maxNonNegTrailingSubArraySum = 0;
      itMaxNonNegTrailingSubArrayBegin = itMaxNonNegTrailingSubArrayEnd;
    }
    else {
      maxNonNegTrailingSubArraySum = trailingSubArraySum;
    }
  }
}

// O(N^2) brute force search
void findMaxSubArrayBruteForce(const vector<int>::iterator& inpSeqBegin, const vector<int>::iterator& inpSeqEnd,
  vector<int>::iterator& itMaxSubArrayBegin, vector<int>::iterator& itMaxSubArrayEnd, int& maxSubArraySum)
{
  for (auto begin = 0; begin < std::distance(inpSeqBegin, inpSeqEnd); ++begin) {
    for (auto end = begin+1; end <= std::distance(inpSeqBegin, inpSeqEnd); ++end) {
      const int currentSubArraySum = std::accumulate(inpSeqBegin + begin, inpSeqBegin + end, 0);
      if (currentSubArraySum > maxSubArraySum) {
        maxSubArraySum = currentSubArraySum;
        itMaxSubArrayBegin = inpSeqBegin + begin;
        itMaxSubArrayEnd = inpSeqBegin + end;
      }
    }
  }
}


int main() {
  vector<int> inputSequence(20);
  std::srand(time(0));
  std::generate_n(inputSequence.begin(), inputSequence.size(), [](){return std::rand() % 100 -50; });
  assert(inputSequence.size() > 0);
  cout << "input sequence: ";
  std::copy(inputSequence.begin(), inputSequence.end(), std::ostream_iterator<int>(std::cout, " "));
  cout << "\n";
  vector<int>::iterator itMaxSubArrayBegin = inputSequence.begin();
  vector<int>::iterator itMaxSubArrayEnd = inputSequence.begin();
  int maxSubArraySum = -200;
  findMaxSubArray(inputSequence.begin(), inputSequence.end(), itMaxSubArrayBegin, itMaxSubArrayEnd, maxSubArraySum);
  std::copy(itMaxSubArrayBegin, itMaxSubArrayEnd, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\nsum: " << maxSubArraySum << "\n";

  itMaxSubArrayBegin = inputSequence.begin();
  itMaxSubArrayEnd = inputSequence.begin();
  maxSubArraySum = -200;
  findMaxSubArrayBruteForce(inputSequence.begin(), inputSequence.end(), itMaxSubArrayBegin, itMaxSubArrayEnd, maxSubArraySum);
  std::copy(itMaxSubArrayBegin, itMaxSubArrayEnd, std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\nsum: " << maxSubArraySum << "\n";
  return 0;
}
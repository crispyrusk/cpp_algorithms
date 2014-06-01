// http://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/
/*
Minimum number of jumps to reach end
Given an array of integers where each element represents the max number of steps that can be made forward from that element. 
Write a function to return the minimum number of jumps to reach the end of the array (starting from the first element). If an element is 0, then cannot move through that element.
*/
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main() {
  const std::vector<int> vec = { 1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9 };
  int numElements = vec.size();
  std::vector<int> minJump(numElements, 1000);
  std::vector<int> route;
  minJump[numElements - 1] = 0;
  for (int n = numElements - 2; n >= 0; --n) {
    auto numPossibleSteps = vec[n];
    auto itBegin = minJump.begin() + n;
    auto itEnd = itBegin + std::min(numPossibleSteps+1, numElements - n);
    auto minFromNextStep = std::min_element(itBegin, itEnd);
    route.push_back(std::distance(minJump.begin(), minFromNextStep));
    minJump[n] = 1 + *minFromNextStep;
  }
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ","));
  std::copy(minJump.begin(), minJump.end(), std::ostream_iterator<int>(std::cout, ","));
  return 0;
}
#include <iostream>
#include <iterator>
#include <cassert>

float getSqrtNewtonRhapson(const float x, const float precision) {
  assert(x >= 0.0);
  assert(precision > 0.0);
  float sqrtx = x;
  while (abs(pow(sqrtx, 2.0) - x) > precision) {
    assert(sqrtx > 0.0);
    sqrtx = 0.5 * (sqrtx + x/sqrtx);
  }
  return sqrtx;
}

float getSqrtBinaryIntervalSearch(const float x, const float precision) {
  assert(x >= 0.0);
  assert(precision > 0.0);
  float sqrtx = 0.0;
  float stepSize = 10.0; // initial step size
  bool direction = false; // true means I am in the upper interval, false means I am in the lower interval
  while (abs(pow(sqrtx, 2.0) - x) > precision) {
    if (pow(sqrtx, 2.0) - x < 0.0) {
      if (direction == true) {
        direction = false;
        stepSize = -stepSize / 2.0;
      }
    }
    else {
      if (direction == false) {
        direction = true;
        stepSize = -stepSize / 2.0;
      }
    }
    sqrtx += stepSize;
  }
  return sqrtx;
}

int main() {
  std::cout << "2.0:" << getSqrtNewtonRhapson(2.0, 0.01) << ", 0.01:" << getSqrtNewtonRhapson(0.01, 0.001) << std::endl;
  std::cout << "2.0:" << getSqrtBinaryIntervalSearch(2.0, 0.01) << ", 0.01:" << getSqrtBinaryIntervalSearch(0.01, 0.001) << std::endl;
  return 0;
}

#include <iostream>

class A {
  int count;
  int* arr;
  A(const A& rhs);
  A& operator=(const A&rhs);
};

A::A(const A& rhs) {
  count = rhs.count;

}

int main() {
  return 0;
}
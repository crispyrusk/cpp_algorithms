#include <iostream>
#include <iterator>
#include <utility>

class A {
public:
  A(const int n);
  // big three
  A(const A& rhs);
  A& operator=(const A&rhs);
  ~A();
  // Note - not implementing move constructor
  void print() const;
  int count;
  int* arr;
private:
  // and half
  void swap(A& lhs, A& rhs) throw();
};

A::A(const int n) : count(n), 
                    arr(count ? new int[count] : 0) 
{}

// copy constructor
A::A(const A& rhs) : count(rhs.count),
                     arr(count? new int[count]: 0)
{
  for (int i = 0; i < count; ++i) {
    arr[i] = rhs.arr[i];
  }
}

// destructor
A::~A() {
  delete[] arr;
}

// assignment operator with copy-swap
A& A::operator=(const A& rhs) {
  // copy
  A temp(rhs);
  // swap
  swap(*this, temp);
  return *this;
}

// Note that this swap does not throw
// where STL swap may throw because it is implemented using copy and assignment operators internally
void A::swap(A& lhs, A& rhs) throw() {
  std::swap(lhs.count, rhs.count);
  std::swap(lhs.arr, rhs.arr);
}

void A::print() const {
  if (count) {
    std::copy(arr, arr + count, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
  }
}

int main() {
  const int N = 10;
  A a(N);
  for (int i = 0; i < N; ++i) {
    a.arr[i] = i;
  }
  a.print();
  A a1(a);
  a1.print();
  A a2(N);
  a2.print();
  a2 = a;
  a2.print();
  return 0;
}
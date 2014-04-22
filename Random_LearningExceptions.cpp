#include <iostream>


class A {
public:
  int i;
  A(int i_arg) : i(i_arg) {
    std::cout << "A created with " << i << std::endl;
  }
  ~A() {
    std::cout << "A destructed" << std::endl;
  }
};

int main() {
  try {
    A a1(100);
    throw - 1;
    A a2(200);
  } // RAII kicks in here - a1 is destroyed here; 
    // note a2 constructor never called - constructor is not called - may be memory is allocated for it and then deallocated with the try scope - dont know for sure
  catch (int exceptCode) {
    std::cerr << "caught exception" << exceptCode << std::endl;
  }
  A a3(300);
  return 0;
}
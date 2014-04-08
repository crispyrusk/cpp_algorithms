// Nested templating with function pointer

#include <iostream>

void fn1() {
  std::cout << "fn1" << std::endl;
}

void fn2() {
  std::cout << "fn2" << std::endl;
}

template<void(*FP)()>
void testFuncPointer_1() {
  std::cout << "inside templated function 1" << std::endl;
  FP();
  std::cout << "done templated function 1" << std::endl;
}

template<void(*FP)()>
void testFuncPointer_2() {
  std::cout << "inside templated function 2"  << std::endl;
  testFuncPointer_1<FP>();
  std::cout << "done templated function 2" << std::endl;
}


template<typename T>
void testFunctionPointer_3(T t) {
  std::cout << "inside templated function 3" << std::endl;
  t();
  std::cout << "done templated function 3" << std::endl;
}


template<typename T>
void testFunctionPointer_4(T t) {
  std::cout << "inside templated function 4" << std::endl;
  testFunctionPointer_3<void(*)()>(t);
  std::cout << "done templated function 4" << std::endl;
}

int mainNestingTemplates() {
  testFuncPointer_2<fn1>();
  testFuncPointer_2<fn2>();

  testFunctionPointer_4<void(*)()>(fn1);
  testFunctionPointer_4<void(*)()>(fn2);
  return 0;
}

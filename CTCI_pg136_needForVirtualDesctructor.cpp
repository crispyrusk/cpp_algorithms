// whenever you derive a class, make sure if you need to have a virtual destructor
//   Derived(const int i) : Base(i) { -- when the base class does not have a default constructor
//   remember when Derived is constructed, it first creates the base-class by calling a suitable constructor
#include <iostream>
#include <iterator>
#include <vector>

class Base {
  std::vector<int>* blah;
public:
  Base(const int i) {
    blah = new std::vector<int>(i);
    std::cout << "created blah of base" << std::endl;
  }
  ~Base() {
    delete blah;
    std::cout << "deleted blah of base" << std::endl;
  }
  virtual void whoAmI() {
    std::cout << "I am a Base" << std::endl;
  }
};

class Derived : public Base {
  std::vector<int>* blahDerived;
public:
  Derived(const int i) : Base(i) {
    blahDerived = new std::vector<int>(i);
    std::cout << "created blah of derived" << std::endl;
  }
  ~Derived() {
    delete blahDerived;
    std::cout << "deleted blahDerived" << std::endl;
  }
  virtual void whoAmI() {
    std::cout << "I am a Derived" << std::endl;
  }
};


class BaseWithVirtual {
  std::vector<int>* blah;
public:
  BaseWithVirtual(const int i) {
    blah = new std::vector<int>(i);
    std::cout << "created blah of BaseWithVirtual" << std::endl;
  }
  virtual ~BaseWithVirtual() {
    delete blah;
    std::cout << "deleted blah of BaseWithVirtual" << std::endl;
  }
  virtual void whoAmI() {
    std::cout << "I am a BaseWithVirtual" << std::endl;
  }
};

class DerivedWithVirtual : public BaseWithVirtual {
  std::vector<int>* blahDerivedWithVirtual;
public:
  DerivedWithVirtual(const int i) : BaseWithVirtual(i) {
    blahDerivedWithVirtual = new std::vector<int>(i);
    std::cout << "created blah of DerivedWithVirtual" << std::endl;
  }
  ~DerivedWithVirtual() {
    delete blahDerivedWithVirtual;
    std::cout << "deleted blahDerived" << std::endl;
  }
  virtual void whoAmI() {
    std::cout << "I am a Derived" << std::endl;
  }
};





int main() {
  Base* basePtr = new Base(10);
  basePtr->whoAmI();
  delete basePtr;
  Derived* derivedPtr1 = new Derived(10);
  derivedPtr1->whoAmI();
  delete derivedPtr1;
  // now polymorphic object
  Base* derivedPtr2 = new Derived(10);
  derivedPtr2->whoAmI();
  delete derivedPtr2; // note only the base class constructed is called. The derived constructor is not called ==> memory leak
  std::cout << "with virtual destructor" << std::endl;
  // now polymorphic object
  BaseWithVirtual* derivedPtr3 = new DerivedWithVirtual(10);
  derivedPtr3->whoAmI();
  delete derivedPtr3; // note only the base class constructed is called. The derived constructor is not called ==> memory leak

  return 0;
}
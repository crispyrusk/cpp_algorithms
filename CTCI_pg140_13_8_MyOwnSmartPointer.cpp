// remember the object reference and 
// reference count should be pointers
#include <iostream>
#include <iterator>
#include <cassert>

template<typename T>
class SmartPointer {
public:
  SmartPointer(T* objArg) {
    obj = objArg;
    refCount = (unsigned int*)std::malloc(sizeof(unsigned int)* 1);
    assert(refCount != nullptr);
    *refCount = 1;
  }
  SmartPointer(const SmartPointer<T>& rhs) {
    obj = rhs.obj;
    refCount = rhs.refCount;
    ++(*refCount);
  }

  SmartPointer<T>& operator=(const SmartPointer<T>& rhs) {
    //copy
    SmartPointer<T> temp(rhs); 
    // myswap
    std::swap(obj, temp.obj);
    std::swap(refCount, temp.refCount);
    return *this;
  }

  ~SmartPointer() {
    std::cout << "at destructor ref count " << *refCount << "\n";
    --(*refCount);
    if (*refCount == 0) {
      delete obj;    
      free(refCount);
    }
  }
  T* obj;
  unsigned* refCount;
};

int main() {
  SmartPointer<int> sp(new int(10));
  SmartPointer<int> sp2(sp);
  SmartPointer<int> sp3(sp);
  sp3 = sp2;
  std::cout << *(sp3.refCount) << "\n";
  return 0;
}

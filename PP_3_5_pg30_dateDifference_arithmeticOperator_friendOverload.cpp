// mafrin note: 
/*
http://www.learncpp.com/cpp-tutorial/92-overloading-the-arithmetic-operators/
Overloading operators using friend functions

When the 
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
operator does not modify its operands, the best way to overload the operator is via friend function.
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
None of the arithmetic operators modify their operands (they just produce and return a result), so we will
utilize the friend function overloaded operator method here.

Similar logic of friend ostream& operator<<(ostream& o, MyClass& obj)
*/

#include <iostream>
#include <iterator>
#include <cassert>
#include <ostream>

class Date {
  int yyyy=2000;
  int mm=1;
  int dd=1;
public:
  Date(int yyyyArg, int mmArg, int ddArg) : yyyy(yyyyArg), mm(mmArg), dd(ddArg) {}
  friend Date operator-(const Date& date1, const Date& date2);
  friend std::ostream&  operator<<(std::ostream& o, const Date& d);
};

std::ostream&  operator<<(std::ostream& o, const Date& d) {
  o << d.yyyy << "/" << d.mm << "/" << d.dd;
  return o;
}

Date operator-(const Date& date1, const Date& date2) {
  Date rtrn(date1);
  if (rtrn.dd <= date2.dd) {
    --(rtrn.mm);
    rtrn.dd = rtrn.dd + 30 - date2.dd;
  }
  else {
    rtrn.dd -= date2.dd;
  }
  if (rtrn.mm <= date2.mm) {
    --(rtrn.yyyy);
    rtrn.mm = rtrn.mm + 12 - date2.mm;
  }
  else {
    rtrn.mm -= date2.mm;
  }
  if (rtrn.yyyy < date2.yyyy) {
    assert(false);
  }
  else {
    rtrn.yyyy -= date2.yyyy;
  }
  return rtrn;
}

int main(){
  Date date1(2014, 10, 1);
  Date date2(2014, 8, 1);
  std::cout << (date1 - date2) << std::endl;
  return 0;
}
                                                                                                                

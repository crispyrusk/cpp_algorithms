#include <string>
#include <iostream>

void reverse(char* str) {
  char* end = str;
  char* begin = str;
  char tmp;
  while (*end != '\0') {
    ++end;
  }
  --end;
  while (begin < end) {
    tmp = *begin;
    *begin = *end;
    *end = tmp;
    ++begin; --end;
  }
}

void reverse(std::string& str) {
  auto itEnd = str.end()-1;
  for (auto it = str.begin(); (it != str.end()) && (itEnd > it); ++it, --itEnd) {
    std::swap(*it, *itEnd);
  }
}

int mainReverseString() {
  std::string testString{ "this is a test string" }; // c++11 init list
  std::cout << "input:" << testString << std::endl;
  reverse(testString);
  std::cout << "output:" << testString << std::endl;
  char testString2[] = "this is another test string";
  std::cout << "input2:" << testString2 << std::endl;
  reverse(testString2);
  std::cout << "output2:" << testString2 << std::endl;
  return 0;
}
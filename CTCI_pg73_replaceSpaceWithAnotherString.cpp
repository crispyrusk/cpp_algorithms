// replace every space with "%20s" 
// trick is to iterate from end of the string
// my excersie is to use rbegin and rend

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

void doReplace(std::string& str, const std::string& repString) {
  std::size_t strSize = str.size();
  std::size_t repStringSize = repString.size();
  int numSpaces = std::count_if(str.begin(), str.end(), [](const char x){return x == ' '; });
  str.resize(str.size() + numSpaces*(repStringSize-1), ' ');
  for (
    std::string::reverse_iterator rIt = str.rbegin() + numSpaces*(repStringSize-1), rIt2 = str.rbegin(); 
    rIt != str.rend(); ++rIt) {
    assert(rIt2 <= rIt);
    if (*rIt == ' ') {
      std::copy(repString.rbegin(), repString.rend(), rIt2);
      rIt2 += repString.size();
    }
    else {
      *rIt2 = *rIt;
      ++rIt2;
    }
  }
}


int mainReplaceSpaces() {
  std::string testString = { "Mr. John Smith" };
  std::string replaceString = {"%20s"};
  doReplace(testString, replaceString);
  return 0;
}
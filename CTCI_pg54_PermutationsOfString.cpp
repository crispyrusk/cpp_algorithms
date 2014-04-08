// output a set of permutations of a given string
// using recursion
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <iterator>
#include <cassert>

void constructPerm(std::string substring, std::set<std::string>& permOfPrefix) {
  if(substring.size()==0) {
    return;
  }
  std::set<std::string> newPermOfPrefix;
  for(std::string x : permOfPrefix) {
    for(std::size_t pos = 0; pos <= x.size(); ++pos) {
      auto x_copy = x;
      x_copy.insert(x_copy.begin()+pos, substring.begin(), substring.begin()+1);
      newPermOfPrefix.insert(x_copy);
    }
  }
  permOfPrefix = newPermOfPrefix;
  constructPerm(substring.substr(1), permOfPrefix);
}

int mainPermutationsOfString() {
  std::string testString="abcd";
  std::string::iterator itEnd = std::unique(testString.begin(), testString.end());
  assert(itEnd == testString.end());
  std::set<std::string> permOfString;
  permOfString.insert("");
  constructPerm(testString, permOfString);
  std::copy(permOfString.begin(), permOfString.end(),
            std::ostream_iterator<std::string>(std::cout, " "));
  return 0;
}
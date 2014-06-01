#include <iostream>
#include <unordered_map>
#include <list>

void populateHashTable(const std::vector<std::string>& unallowedStrings, std::unordered_map<std::string, bool>& hashMap) {
  for (int i = 0; i < unallowedStrings.size(); ++i) {
    hashMap[unallowedStrings[i]] = true;
  }
}

void removeUnallowedStringsFromLongList(std::list<std::string>& longListOfStrings, const std::unordered_map<std::string, bool>&unallowedStringsHashTable) {
  longListOfStrings.remove_if([&unallowedStringsHashTable](const std::string str){return unallowedStringsHashTable.count(str)>0; });
}

int main()  {
  std::list<std::string> longListOfStrings;
  longListOfStrings.push_back("baba");
  longListOfStrings.push_back("black");
  longListOfStrings.push_back("sheep");
  longListOfStrings.push_back("spider");
  std::vector<std::string> unallowedStrings;
  unallowedStrings.push_back("heap"); 
  unallowedStrings.push_back("foo");
  unallowedStrings.push_back("baba");
  unallowedStrings.push_back("spider");
  std::unordered_map<std::string, bool> unallowedStringsHashTable;
  populateHashTable(unallowedStrings, unallowedStringsHashTable);
  removeUnallowedStringsFromLongList(longListOfStrings, unallowedStringsHashTable);
  return 0;
}
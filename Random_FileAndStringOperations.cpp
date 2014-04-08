// reading from a text file

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int mainReadingFromTextFileAndOperations() {
  std::vector<std::string> vs;
  std::ifstream testFileStream("test_20140407.txt", std::ios::in);
  std::string s;
  while (testFileStream >> s) {
    vs.push_back(s);
  }
  return 0;
}
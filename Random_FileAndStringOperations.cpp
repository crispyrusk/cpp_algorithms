// reading from a text file in a dequee

#include <iostream>
#include <fstream>
#include <string>
#include <deque>

int mainReadingFromTextFileAndOperations() {
  std::deque<std::string> ds;
  std::ifstream testFileStream("test_20140407.txt", std::ios::in);
  std::string s;
  while (testFileStream >> s) {
    ds.push_back(s);
  }
  return 0;
}
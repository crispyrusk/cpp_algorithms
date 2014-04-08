#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> vs;
  std::ofstream testFileStream("test_20140407.txt", std::ios::in);
  std::string s;
  while (testFileStream >> s) {

  }
  return 0;
}
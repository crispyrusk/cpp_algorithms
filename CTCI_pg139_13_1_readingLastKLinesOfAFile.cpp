#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>

int main() {
  auto fin = std::ifstream("test_20140407.txt", std::ios::in);
  std::string line;
  std::vector<std::string> last10Lines(10);
  int newLine = -1;
  while (std::getline(fin, line)) {
    last10Lines[(++newLine) % 10] = line;
  }
  for (int i = 1; i <= 10; ++i) {
    std::cout << last10Lines[(newLine + i) % 10] << "\n";
  }
  return 0;
}
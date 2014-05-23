// std::getline to read from cin until empty input (read from stdin using cin and getline)
// std::getline - gets \n terminated strings from string_buffer
// string compare - compares if two strings are the same

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
#include <cassert>

namespace {
  const int radix = 3; // size of the alphabet
}

void printCharacHistograms(const std::vector<std::string>& strColl, const std::vector<std::vector<int> >& strCharacHistogram) {
  for (std::size_t i = 0; i < strColl.size(); ++i) {
    std::cout << strColl[i] << ";";
    std::copy(strCharacHistogram[i].begin(), strCharacHistogram[i].end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;
  }
}


// for keyIndexSort - the keys beyond a small set - then keys can be mapped to the first N whole numbers
void keyIndexSort(std::vector<int>& indices, std::vector<int>& keys) {
  const int maxKey= *std::max_element(keys.begin(), keys.end());
  std::vector<int> cumSumOfCount(maxKey+2);
  // first find count where key is mapped to index key+1
  for (int key = 0; key <= maxKey; ++key) {
    cumSumOfCount[key + 1] = std::count_if(keys.begin(), keys.end(), [key](const int x) {return x == key; });
  }
  // find the cumsum
  int runningSum = 0;
  for (int key = 0; key <= maxKey + 1; ++key) {
    runningSum += cumSumOfCount[key];
    cumSumOfCount[key] = runningSum;
  }
  // the cumsum gives the location where the keys should be inserted in the sorted order
  std::vector<int> sortedIndices(indices.size());
  for (std::size_t i = 0; i < indices.size(); ++i) {
    const int sortedIndex = cumSumOfCount[keys[i]]++;
    sortedIndices[sortedIndex] = i;
  }
  std::swap(indices, sortedIndices);
}

void sortUsingLSD(std::vector<std::string>& strColl, std::vector<std::vector<int> >& strCharacHistogram) {
  std::cout << "input:\n";
  printCharacHistograms(strColl, strCharacHistogram);
  for (int digit = 0; digit < radix; ++digit) {
    // for index, key vectors
    std::vector<int> indices(strColl.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::vector<int> keys(strColl.size());
    for (std::size_t i = 0; i < strColl.size(); ++i) {
      keys[i] = strCharacHistogram[i][digit]; // looks like a wasteful copy
    }
    keyIndexSort(indices, keys);
    auto sortedStrColl = strColl;
    auto sortedStrCharacHistogram = strCharacHistogram;
    for (std::size_t i = 0; i < strColl.size(); ++i) {
      sortedStrColl[i] = strColl[indices[i]];
      sortedStrCharacHistogram[i] = strCharacHistogram[indices[i]];
    }
    std::swap(sortedStrColl, strColl);
    std::swap(sortedStrCharacHistogram, strCharacHistogram);
    std::cout << "digit:" << digit << "\n";
    printCharacHistograms(strColl, strCharacHistogram);
  }
}


void populateCharacHistograms(std::vector<std::string>& strColl, std::vector<std::vector<int> >& strCharacHistogram) {
  for (auto& hist : strCharacHistogram) {
    hist.resize(radix, 0);
  }
  for (std::size_t i = 0; i < strColl.size(); ++i) {
    auto const& str = strColl[i];
    std::for_each(str.begin(), str.end(), 
      [&strCharacHistogram, i](const char x)
    {
      auto const pos = x - 'a';
      if (pos >= 0 && pos < radix) {
        ++strCharacHistogram[i][pos];
      }
    });
  }
}


int main() {
  std::vector<std::string> strColl;
  /*
  for (std::string str; std::getline(std::cin, str);) {
    if (str.compare(std::string("")) == 0) {
      break;
    }
    std::cout << str << "\n";
    strColl.push_back(str);
  }*/

  strColl.push_back("abc"); 
  strColl.push_back("acb");
  strColl.push_back("bac");
  strColl.push_back("bca");
  strColl.push_back("cca");
  strColl.push_back("cac");
  strColl.push_back("acc");
  strColl.push_back("bba");
  strColl.push_back("bab");

  std::vector<std::vector<int> > strCharacHistogram(strColl.size());
  populateCharacHistograms(strColl, strCharacHistogram);
  printCharacHistograms(strColl, strCharacHistogram);
  sortUsingLSD(strColl, strCharacHistogram); // when we sort the string based on the charac histogram, the anagrams will be close to each // LSD is stable sort
  return 0;
}

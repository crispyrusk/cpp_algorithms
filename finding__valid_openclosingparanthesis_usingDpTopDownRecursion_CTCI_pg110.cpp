// note map[key] returns value_ref
// map.find(key) return iterator (points to the actual key-value object), and it->first and it->second. So modiygin it->second, will modify things
// you could use map::count to find and and then use []

#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <cassert>

const std::set<std::string>& getAllValidParanPairString(std::map<std::pair<int, int>, std::set<std::string> >& dpCache,
  const int remLefParan, const int remRightParan) {
  assert(remLefParan <= remRightParan);
  auto searchPair = std::make_pair(remLefParan, remRightParan);
  /*
  auto itSearch = dpCache.find(searchPair);
  if (itSearch != dpCache.end()) {
    return itSearch->second;
  }
  */
  if (dpCache.count(searchPair) > 0) {
    return dpCache[searchPair];
  }
  if (remLefParan == 0 && remRightParan == 0) {
    dpCache[searchPair] = std::set<std::string>();
    dpCache[searchPair].insert(std::string(""));
    return dpCache[searchPair];
  }
  std::set<std::string> currentValidParanPairString;
  if (remLefParan > 0) {
    auto const& s = getAllValidParanPairString(dpCache, remLefParan - 1, remRightParan);
    for (auto x : s) {
      x.insert(0, std::string("("));
      currentValidParanPairString.insert(x);
    }
  }
  if (remRightParan > remLefParan) {
    auto const& s = getAllValidParanPairString(dpCache, remLefParan, remRightParan - 1);
    for (auto x : s) {
      x.insert(0, std::string(")"));
      currentValidParanPairString.insert(x);
    }
  }
  dpCache[searchPair] = currentValidParanPairString;
  return dpCache[searchPair];
}

int main() {
  const int numParanPairs = 3;
  std::map<std::pair<int, int>, std::set<std::string> > dpCache;
  auto const& x = getAllValidParanPairString(dpCache, numParanPairs, numParanPairs);
  std::copy(x.begin(), x.end(), std::ostream_iterator<std::string>(std::cout, ","));
  return 0;
}

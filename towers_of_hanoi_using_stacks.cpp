#include <iostream>
#include <iterator>
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

void init(vector<stack<int> >& towers, const int NumDiscs) {
  stack<int> discs;
  for (int i = 0; i < NumDiscs; ++i) {
    discs.push(i);
  }
  towers[0] = move(discs);

}

void printStack(stack<int> s) {
  if (s.empty()) { return; }
  auto const temp = s.top();
  s.pop();
  printStack(s);
  s.push(temp);
  cout << temp << ",";
}

void printTowers(vector<stack<int> >& towers) {
  for (auto& tower : towers) {
    cout << "stack: ";
    printStack(tower);
    cout << "\n";
  }
  cout << "########\n";
}

void moveTopDisc(vector<stack<int> >& towers, const int source, const int target) {
  const int top = towers[source].top();
  towers[source].pop();
  towers[target].push(top);
}

void moveDiscs(std::vector<std::stack<int> >& towers, const int numDiscs, const int source, const int target, const int temp) {
  if (numDiscs <= 0) { return;  }
  moveDiscs(towers, numDiscs - 1, source, temp, target);
  moveTopDisc(towers, source, target);
  moveDiscs(towers, numDiscs - 1, temp, target, source);
  printTowers(towers);
}

int main() {
  const int NumDiscs = 4;
  vector<stack<int> > towers(3);
  init(towers, NumDiscs);
  moveDiscs(towers, NumDiscs, 0, 2, 1);
  return 0;
}

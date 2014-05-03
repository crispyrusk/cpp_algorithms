#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <stack>
#include <cassert>
#include <string>

class DiGraph {
public:
  std::vector<std::set<int> > adj;
  DiGraph(int numVertices) { adj.resize(numVertices); }
  void insertArc(std::string arc);
  void constructGraphFromArcs(std::string graph);
  void printDiGraph();
};

void DiGraph::printDiGraph() {
  for (auto it = adj.begin(); it != adj.end(); ++it) {
    std::cout << "node:" << std::distance(adj.begin(), it) << " neighbors:";
    std::copy(it->begin(), it->end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << "\n";
  }
}

void DiGraph::constructGraphFromArcs(std::string graph) {
  auto itMover = graph.begin();
  while (itMover != graph.end()) {
    auto openBraceIt = std::find(itMover, graph.end(), '(');
    auto closeBraceIt = std::find(itMover, graph.end(), ')');
    if (openBraceIt == graph.end() || closeBraceIt == graph.end()) { return; }
    assert(openBraceIt + 1 != graph.end());
    auto posOpenBracePlusOne = std::distance(graph.begin(), openBraceIt + 1);
    auto len = std::distance(openBraceIt + 1, closeBraceIt);
    insertArc(graph.substr(posOpenBracePlusOne, len));
    itMover = closeBraceIt + 1;
  }
}

void DiGraph::insertArc(std::string arc) {
  assert(std::find(arc.begin(), arc.end(), ')') == arc.end());
  assert(std::find(arc.begin(), arc.end(), '(') == arc.end());
  auto itComma = std::find(arc.begin(), arc.end(), ',');
  if (itComma == arc.end()) { return; }
  std::string v1Temp(arc.begin(), itComma);
  assert(itComma + 1 != arc.end());
  std::string v2Temp(itComma + 1, arc.end());
  auto v1 = std::stoi(v1Temp);
  auto v2 = std::stoi(v2Temp);
  assert(v1 < static_cast<int>(adj.size()));
  assert(v2 < static_cast<int>(adj.size()));
  adj[v1].insert(v2);
}

class TopoSort {
public:
  TopoSort(const DiGraph& gArg);
  void printSchedule();
private:
  const DiGraph& g;
  const int rootVertex = -1;
  bool hasCycle = false;
  std::vector<bool> visited;
  std::vector<bool> returned; // needed to check for loops
  std::stack<int> reverseOrder;
  bool doDFS(const int rootOfSubTree);
};

TopoSort::TopoSort(const DiGraph& gArg) :
g(gArg)
{
  const int numVertices = static_cast<int>(g.adj.size());
  visited.resize(numVertices, false);
  returned.resize(numVertices, false);
  for (int i = 0; i < numVertices; ++i) {
    if (visited[i]) {
      assert(returned[i]);
    }
    else {
      hasCycle = doDFS(i) || hasCycle;
    }
  }
}

bool TopoSort::doDFS(const int rootOfSubTree) {
  assert(!visited[rootOfSubTree]);
  visited[rootOfSubTree] = true;
  bool cycleDetected = false;
  for (auto const neighbor : g.adj[rootOfSubTree]) {
    if (!visited[neighbor]) {
      cycleDetected = doDFS(neighbor) || cycleDetected; 
    }
    else {
      cycleDetected = !returned[neighbor] || cycleDetected;
    }
  }
  returned[rootOfSubTree] = true;
  reverseOrder.push(rootOfSubTree);
  return cycleDetected;
}


void TopoSort::printSchedule() {
  std::cout << "schedule: ";
  if (hasCycle) {
    std::cout << "no feasible schedule; graph has cycle \n";
    return;
  }
  std::stack<int> tempStack(reverseOrder);
  while (!tempStack.empty()) {
    std::cout << tempStack.top() << ", ";
    tempStack.pop();
  }
  std::cout << std::endl;
}

int main() {
  DiGraph g(7);
  std::string inputGraph = { "(0,1),(0,5),(0,2),(3,6),(3,5),(3,4),(5,2),(6,4),(6,0), (3,2),(1,4)" };
  //std::cin >> inputGraph;
  g.constructGraphFromArcs(inputGraph);
  g.printDiGraph();
  TopoSort schedule(g);
  schedule.printSchedule();

  DiGraph g1(7);
  std::string inputGraphWithCycle = { "(0,1),(0,5),(0,2),(3,6),(3,5),(3,4),(5,2),(4,6),(6,0),(3,2),(1,4)" };
  g1.constructGraphFromArcs(inputGraphWithCycle);
  g1.printDiGraph();
  TopoSort schedule1(g1);
  schedule1.printSchedule();
  return 0;
}
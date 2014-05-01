#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cassert>

// undirected graph
class UdGraph {
public:
  std::vector<std::set<int> > adj;
  UdGraph(int numVertices) { adj.resize(numVertices); };
  void insertEdge(std::string edge);
  void constructGraphFromEdges(std::string graph);
  void printGraph();
};

void UdGraph::printGraph() {
  for (auto it = adj.begin(); it!= adj.end(); ++it) {
    std::cout << "node:" << std::distance(adj.begin(), it) << " neighbors:";
    std::copy(it->begin(), it->end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << "\n";
  }
}

void UdGraph::constructGraphFromEdges(std::string graph) {
  auto itMover = graph.begin();
  while (itMover != graph.end()) {
    auto openBraceIt = std::find(itMover, graph.end(), '(');
    auto closeBraceIt = std::find(itMover, graph.end(), ')');
    if (openBraceIt == graph.end() || closeBraceIt == graph.end()) { return; }
    assert(openBraceIt + 1 != graph.end());
    auto posOpenBracePlusOne = std::distance(graph.begin(), openBraceIt + 1);
    auto len = std::distance(openBraceIt + 1, closeBraceIt);
    insertEdge(graph.substr(posOpenBracePlusOne, len));
    itMover = closeBraceIt + 1;
  }
}

void UdGraph::insertEdge(std::string edge) {
  assert(std::find(edge.begin(), edge.end(), ')') == edge.end());
  assert(std::find(edge.begin(), edge.end(), '(') == edge.end());
  auto itComma = std::find(edge.begin(), edge.end(), ',');
  if (itComma == edge.end()) { return; }
  std::string v1Temp(edge.begin(), itComma);
  assert(itComma + 1 != edge.end());
  std::string v2Temp(itComma + 1, edge.end());
  auto v1 = std::stoi(v1Temp);
  auto v2 = std::stoi(v2Temp);
  assert(v1 < static_cast<int>(adj.size()));
  assert(v2 < static_cast<int>(adj.size()));
  adj[v1].insert(v2);
  adj[v2].insert(v1);
}


int main() {
  UdGraph g(10);
  std::string inputGraph = {"(1,2),(1,3),(1,4),(4,5),(2,6),(6,5),(8,9),(3,8)"};
  //std::cin >> inputGraph;
  g.constructGraphFromEdges(inputGraph);
  g.printGraph();
  return 0;
}
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>
#include <memory>
#include <string>
#include <algorithm>
#include <cassert>

namespace {
  const int LARGE_INT = std::numeric_limits<int>::max();
}

class WeightedArc {
public:
  WeightedArc(int vArg, int wArg, int weightArg):
  v(vArg), w(wArg), weight(weightArg) { ; }
  int inVertex() const { return v; }
  int outVertex() const { return w; }
  int getArcWeight() const { return weight; }
  bool operator<(const WeightedArc& rhsEdge) { return (weight < rhsEdge.getArcWeight()); }
  bool operator>(const WeightedArc& rhsEdge) { return (weight > rhsEdge.getArcWeight()); }
  bool operator==(const WeightedArc& rhsEdge) { return (weight == rhsEdge.getArcWeight()); }
  friend std::ostream& operator<<(std::ostream& o, const WeightedArc& a);
 private:
  int v = -1;
  int w = -1;
  int weight = -LARGE_INT;
};

std::ostream& operator<<(std::ostream& o, const WeightedArc& a) {
  o << "(" << a.inVertex() << ", " << a.outVertex() << ")";
  return o;
}

class ArcWeightedDiGraph {
public:
  std::vector<std::vector<std::shared_ptr<WeightedArc> > > adj;
  ArcWeightedDiGraph(int numVertices) { adj.resize(numVertices); }
  void insertArc(std::string a);
  void constructGraphFromArcs(std::string graph);
  void printDiGraph();
};

void ArcWeightedDiGraph::printDiGraph() {
  for (auto it = adj.begin(); it != adj.end(); ++it) {
    std::cout << "node:" << std::distance(adj.begin(), it) << " neighbors:";
    for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
      std::cout << *(*it2) << ",";
    }
    std::cout << "\n";
  }
}

void ArcWeightedDiGraph::constructGraphFromArcs(std::string graph) {
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

void ArcWeightedDiGraph::insertArc(std::string arc) {
  assert(std::find(arc.begin(), arc.end(), ')') == arc.end());
  assert(std::find(arc.begin(), arc.end(), '(') == arc.end());
  auto itComma1 = std::find(arc.begin(), arc.end(), ',');
  if (itComma1 == arc.end()) { return; }
  std::string v1Temp(arc.begin(), itComma1);
  assert(itComma1 + 1 != arc.end());
  auto itComma2 = std::find(itComma1 + 1, arc.end(), ',');
  assert(itComma2 != arc.end());
  std::string v2Temp(itComma1 + 1, itComma2);
  assert(itComma2 + 1 != arc.end());
  std::string v3Temp(itComma2 + 1, arc.end());
  auto v = std::stoi(v1Temp);
  auto w = std::stoi(v2Temp);
  auto weight = std::stoi(v3Temp);
  assert(v < static_cast<int>(adj.size()));
  assert(w < static_cast<int>(adj.size()));
  auto arcPtr = std::make_shared<WeightedArc>(v, w, weight);
  adj[v].push_back(arcPtr);
}


class DijkstraSP {
public:
  std::vector<int> spTreeVertices;
  std::vector<int> parentTo;
  DijkstraSP(const ArcWeightedDiGraph& gArg) : g(gArg) { construct(); }
  void print();
private:
  const ArcWeightedDiGraph& g;
  void construct();
  void updatePQFromNode(const int gateway, const std::vector<int>& openNodes,
    std::vector<int>& nodeKeys, std::vector<int>& currentParentTo);
};

void DijkstraSP::print() {
  std::cout << "tree:";
  assert(spTreeVertices.size() == parentTo.size());
  for (std::size_t i = 0; i < spTreeVertices.size(); ++i) {
    std::cout << "(" << spTreeVertices[i] << ", " << parentTo[i] << "), ";
  }
  std::cout << std::endl;
}

void DijkstraSP::construct() {
  assert(spTreeVertices.empty());
  assert(parentTo.empty());
  auto const numVertices = g.adj.size();
  std::vector<int> openNodes(numVertices, -1);
  std::vector<int> nodeKeys(numVertices, LARGE_INT);
  std::vector<int> currentParentTo(numVertices, -1);
  std::iota(openNodes.begin(), openNodes.end(), 0); 
  nodeKeys[0] = -LARGE_INT;
  auto comp = [&nodeKeys](const int v, const int w) {return nodeKeys[v] > nodeKeys[w]; };
  while (!openNodes.empty()){
    std::make_heap(openNodes.begin(), openNodes.end(), comp);
    // pop min
    auto minPQNode = openNodes.front();
    std::pop_heap(openNodes.begin(), openNodes.end(), comp);
    openNodes.pop_back();

    spTreeVertices.push_back(minPQNode);
    parentTo.push_back(currentParentTo[minPQNode]);
    updatePQFromNode(minPQNode, openNodes, nodeKeys, currentParentTo);
  }
}

void DijkstraSP::updatePQFromNode(const int gateway, const std::vector<int>& openNodes,
  std::vector<int>& nodeKeys, std::vector<int>& currentParentTo) {
  auto neighbors = g.adj[gateway];
  for (auto const& neighbor : neighbors) {
    if (nodeKeys[neighbor->outVertex()] > (nodeKeys[gateway] + neighbor->getArcWeight())) {
      nodeKeys[neighbor->outVertex()] = (nodeKeys[gateway] + neighbor->getArcWeight());
      currentParentTo[neighbor->outVertex()] = gateway;
    }
  }
}

int main() {
  ArcWeightedDiGraph g(7);
  std::string inputGraph = { "(0,1,4),(0,5,3),(0,2,1),(3,6,5),(3,5,7),(3,4,8),(5,2,10),(6,4,9),(6,0,4), (3,2,0),(1,4,3)" };
  g.constructGraphFromArcs(inputGraph);
  g.printDiGraph();
  std::cout << "##############################\n";
  DijkstraSP sp(g);
  sp.print();
  return 0;
}
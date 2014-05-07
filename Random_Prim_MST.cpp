// learning friend ostream operator
// learning make_heap, push_heap, pop_heap
// remember make_heap does a max heap
// pop_heap takes the front and put it at the back and maitains (to memorize, swap front and back, and the downheapify new front)
// note pop_heap should be followed by pop_back()
// push_heap pushes to the end of the heap and does an upheapify
// note push_heap should be preceded with push_back()
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <memory>
#include <numeric>
#include <string>
#include <cassert>

namespace {
  int LARGE_INT = std::numeric_limits<int>::max();
}

class WeightedEdge {
public:
  WeightedEdge(int vArg, int wArg, int weightArg) : v(vArg), w(wArg), weight(weightArg) { ; }
  int any() const { return v; };
  int other(int vArg) const { assert(vArg == v || vArg == w); return vArg == v ? w : v; }
  int getEdgeWeight() const { return weight; }
  bool operator<(const WeightedEdge& rhsEdge) { return (weight < rhsEdge.getEdgeWeight());}
  bool operator>(const WeightedEdge& rhsEdge) { return (weight > rhsEdge.getEdgeWeight()); }
  bool operator==(const WeightedEdge& rhsEdge) { return (weight == rhsEdge.getEdgeWeight()); }
  friend std::ostream& operator<<(std::ostream& o, const WeightedEdge& wedge);
private:
  int v = -1;
  int w = -1;
  int weight = -LARGE_INT;
};

std::ostream& operator<<(std::ostream& o, const WeightedEdge& wedge) {
  o << "(" << wedge.v << ", " << wedge.w << ", " << wedge.weight << ")";
  return o;
}

class EdgeWeightedGraph {
public:
  std::vector<std::vector<std::shared_ptr<WeightedEdge> > > adj;
  EdgeWeightedGraph(int numVertices) { adj.resize(numVertices); }
  void insertEdge(std::string edge);
  void constructGraphFromEdges(std::string graph);
  void printGraph();
};

void EdgeWeightedGraph::printGraph() {
  for (auto it = adj.begin(); it != adj.end(); ++it) {
    std::cout << "node:" << std::distance(adj.begin(), it) << " neighbors:";
    for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
      std::cout << *(*it2) << ",";
    }
    std::cout << "\n";
  }
}

void EdgeWeightedGraph::constructGraphFromEdges(std::string graph) {
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

void EdgeWeightedGraph::insertEdge(std::string edge) {
  assert(std::find(edge.begin(), edge.end(), ')') == edge.end());
  assert(std::find(edge.begin(), edge.end(), '(') == edge.end());
  auto itComma1 = std::find(edge.begin(), edge.end(), ',');
  if (itComma1 == edge.end()) { return; }
  std::string v1Temp(edge.begin(), itComma1);
  assert(itComma1 + 1 != edge.end());
  auto itComma2 = std::find(itComma1 + 1, edge.end(), ',');
  assert(itComma2 != edge.end());
  std::string v2Temp(itComma1 + 1, itComma2);
  assert(itComma2 + 1 != edge.end());
  std::string v3Temp(itComma2 + 1, edge.end());
  auto v = std::stoi(v1Temp);
  auto w = std::stoi(v2Temp);
  auto weight = std::stoi(v3Temp);
  assert(v < static_cast<int>(adj.size()));
  assert(w < static_cast<int>(adj.size()));
  auto edgePtr = std::make_shared<WeightedEdge>(v, w, weight);
  adj[v].push_back(edgePtr);
  adj[w].push_back(edgePtr);
}

class PrimMst {
public:
  std::vector<int> treeVertices;
  std::vector<int> parentTo;
  PrimMst(const EdgeWeightedGraph& gArg) : g(gArg) { construct(); }
  void print();
private:
  const EdgeWeightedGraph& g;
  void construct();
  void updatePQFromNode(const int focusNode, const std::vector<int>& openNodes, 
    std::vector<int>& nodeKeys, std::vector<int>& currentParentTo);
};

void PrimMst::print() {
  std::cout << "tree:";
  assert(treeVertices.size() == parentTo.size());
  for (std::size_t i = 0; i < treeVertices.size(); ++i) {
    std::cout << "(" << treeVertices[i] << ", " << parentTo[i] << "), ";
  }
  std::cout << std::endl;
}

void PrimMst::construct() {
  assert(treeVertices.empty());
  assert(parentTo.empty());
  auto const numVertices = g.adj.size();
  std::vector<int> openNodes(numVertices, -1);
  std::vector<int> nodeKeys(numVertices, LARGE_INT);
  std::vector<int> currentParentTo(numVertices, -1);
  std::iota(openNodes.begin(), openNodes.end(), 0);
  nodeKeys[0] = -LARGE_INT;
  auto comp = [&nodeKeys](const int v, const int w) {return nodeKeys[v] > nodeKeys[w]; };
  while (!openNodes.empty()) {
    std::make_heap(openNodes.begin(), openNodes.end(), comp);
    ///  pop operation consists of 3 steps
    auto minPQNode = openNodes.front();
    std::pop_heap(openNodes.begin(), openNodes.end(), comp); // will put the min at the end
    openNodes.pop_back(); // this is not needed if we maintain order
    ///
    std::cout << nodeKeys[minPQNode] << std::endl;
    treeVertices.push_back(minPQNode);
    parentTo.push_back(currentParentTo[minPQNode]);
    updatePQFromNode(minPQNode, openNodes, nodeKeys, currentParentTo);
  }
}

void PrimMst::updatePQFromNode(const int gateway, const std::vector<int>& openNodes,
                               std::vector<int>& nodeKeys, std::vector<int>& currentParentTo) {
  auto& neighbors = g.adj[gateway];
  for (auto const& neighbor : neighbors) {
    auto const neighborVertex = neighbor->other(gateway);
    if (std::find(openNodes.begin(), openNodes.end(), neighborVertex) != openNodes.end()) {
      if (nodeKeys[neighborVertex] > neighbor->getEdgeWeight()) {
        nodeKeys[neighborVertex] = neighbor->getEdgeWeight();
        currentParentTo[neighborVertex] = gateway;
      }
    }
  }
}

int main() {
  EdgeWeightedGraph g(7);
  std::string inputGraph = { "(0,1,4),(0,5,3),(0,2,1),(3,6,5),(3,5,7),(3,4,8),(5,2,10),(6,4,9),(6,0,4), (3,2,0),(1,4,3)" };
  g.constructGraphFromEdges(inputGraph);
  g.printGraph();
  std::cout << "##############################\n";
  PrimMst mst(g);
  mst.print();
  return 0;
}
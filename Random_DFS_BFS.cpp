#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <stack>
#include <queue>
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


class DepthFirstSearch {
public:
  DepthFirstSearch(const UdGraph& G_arg, const int rootVertex_arg);
  bool isConnectedToRoot(const int vertex);
  void printPathTo(const int vertex);
private:
  int _numVertices = 0;
  int _rootVertex = -1;
  const UdGraph& G;
  std::vector<bool> visited;
  std::vector<int> parent;
  void doDFS(const int rootOfSubTree);
};

DepthFirstSearch::DepthFirstSearch(const UdGraph& G_arg, const int rootVertex_arg) : G(G_arg), _rootVertex(rootVertex_arg) 
{
  _numVertices = static_cast<int>(G.adj.size());
  assert(_rootVertex < _numVertices && _rootVertex >= 0);
  visited.resize(G.adj.size(), false);
  parent.resize(G.adj.size(), -1);
  doDFS(_rootVertex);
}

void DepthFirstSearch::doDFS(const int rootOfSubTree) {
  assert(rootOfSubTree >= 0 && rootOfSubTree < _numVertices);
  visited[rootOfSubTree] = true;
  for (auto const neighbor : G.adj[rootOfSubTree]) {
    if (!visited[neighbor]) {
      doDFS(neighbor);
      parent[neighbor] = rootOfSubTree;
    }
  }
}

bool DepthFirstSearch::isConnectedToRoot(const int vertex) {
  assert(vertex >= 0 && vertex < _numVertices);
  return visited[vertex];
}

void DepthFirstSearch::printPathTo(const int vertex) {
  assert(vertex >= 0 && vertex < _numVertices);
  std::cout << "path from " << _rootVertex << " to " << vertex << ": ";
  if (!visited[vertex]) { std::cout << "no path \n"; return; }
  std::stack<int> path;
  int focusVertex = vertex;
  path.push(focusVertex);
  while (parent[focusVertex] != -1) {
    focusVertex = parent[focusVertex];
    path.push(focusVertex);
  }
  while (!path.empty()) {
    std::cout << path.top() << ",";
    path.pop();
  }
  std::cout << std::endl;
}

class BreadthFirstSearch {
public:
  BreadthFirstSearch(const UdGraph& G_arg, const int rootVertex_arg);
  bool isConnectedToRoot(const int vertex);
  void printPathTo(const int vertex);
private:
  int _numVertices = 0;
  int _rootVertex = -1;
  const UdGraph& G;
  std::vector<bool> marked;
  std::vector<int> parent;
  void _doBFS(); // note, not recursive, unlike DFS
};

BreadthFirstSearch::BreadthFirstSearch(const UdGraph& G_arg, const int rootVertex_arg) :
G(G_arg), _rootVertex(rootVertex_arg)
{
  _numVertices = static_cast<int>(G.adj.size());
  assert(_rootVertex >= 0 && _rootVertex < _numVertices);
  _doBFS();
}

void BreadthFirstSearch::_doBFS() {
  assert(marked.empty());
  assert(parent.empty());
  marked.resize(_numVertices, false);
  parent.resize(_numVertices, -1);
  std::queue<int> vertexQueue;
  vertexQueue.push(_rootVertex);
  marked[_rootVertex] = true;
  while (!vertexQueue.empty()) {
    const int rootOfSubTree = vertexQueue.front();
    vertexQueue.pop();
    for (auto const neighbor : G.adj[rootOfSubTree]) {
      if (!marked[neighbor]) {
        vertexQueue.push(neighbor);
        marked[neighbor] = true;
        parent[neighbor] = rootOfSubTree;
      }
    }
  }
}

bool BreadthFirstSearch::isConnectedToRoot(const int vertex) {
  assert(vertex >= 0 && vertex < _numVertices);
  return marked[vertex];
}

void BreadthFirstSearch::printPathTo(const int vertex) {
  assert(vertex >= 0 && vertex < _numVertices);
  std::cout << "path from " << _rootVertex << " to " << vertex << ": ";
  if (!marked[vertex]) { std::cout << "no path \n"; return; }
  std::stack<int> path;
  int focusVertex = vertex;
  path.push(focusVertex);
  while (parent[focusVertex] != -1) {
    focusVertex = parent[focusVertex];
    path.push(focusVertex);
  }
  while (!path.empty()) {
    std::cout << path.top() << ",";
    path.pop();
  }
  std::cout << std::endl;
}

int main() {
  UdGraph g(10);
  std::string inputGraph = {"(1,2),(1,3),(1,4),(4,5),(2,6),(6,5),(8,9),(3,8)"};
  //std::cin >> inputGraph;
  g.constructGraphFromEdges(inputGraph);
  g.printGraph();
  auto dfsTree = DepthFirstSearch(g, 1);
  for (int i = 0; i < static_cast<int>(g.adj.size()); ++i) {
    dfsTree.printPathTo(i);
  }
  auto bfsTree = BreadthFirstSearch(g, 1);
  for (int i = 0; i < static_cast<int>(g.adj.size()); ++i) {
    bfsTree.printPathTo(i);
  }
  return 0;
}
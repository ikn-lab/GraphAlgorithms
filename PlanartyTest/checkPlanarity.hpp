#ifndef __CHECKPLANARITY__
#define __CHECKPLANARITY__

#include<vector>
#include"graph.hpp"

typedef struct Node{
  int ord, low;
}Node;

typedef class BCDecomposition{
public:
  BCDecomposition(Graph _g);
  Graph GetBC(int v){return bc[v2component[v]];};
  int size(){return bc.size();}
  Graph operator[](const int pos){return bc[pos];};
private:
  void GetAP(int v = 0, int prev = -1);
  void decompose();
  Graph GetInducedSubgraph(std::vector<int> V, std::vector<int> &v2id);
  void dfs(int v, std::vector<int> &V);
  Graph g;
  std::vector<Graph> bc;
  std::vector<int> articulation, v2component, isVisited;
  std::vector<Node> node;
  int v_ord = 0;
}BCDecomposition;

bool checkPlanarity(Graph &g);
#endif // __CHECKPLANARITY__

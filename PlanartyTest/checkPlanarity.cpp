#include<vector>
#include<algorithm>

#include"graph.hpp"
#include"checkPlanarity.hpp"

BCDecomposition::BCDecomposition(Graph _g){
  g = _g;
  node.resize(g.size(), Node{-1, (int)1e9});
  isVisited.resize(g.size(), 0);
  v2component.resize(g.size());
  GetAP();
  decompose();
};

void BCDecomposition::GetAP(int v, int prev){
  int to, cnt = 0;
  node[v].ord = node[v].low = v_ord++;
  bool isAP = false;
  for (int i = g[v][0].next; i != g[v].end(); i=g[v][i].next) {
    to = g[v][i].to;
    if(prev == to)continue;
    cnt += (node[to].ord == -1);
    if(node[to].ord == -1){
      GetAP(to, v); 
      node[v].low = std::min(node[v].low, node[to].low);
      isAP |= ((node[v].ord != 0) and
               (node[v].ord <= node[to].low));
    }
    node[v].low = std::min(node[v].low, node[to].ord);
  }
  if(cnt > 1 and node[v].ord == 0)isAP = true;
  if(isAP){
    articulation.emplace_back(v);
  }
}


Graph BCDecomposition::GetInducedSubgraph(std::vector<int> V, std::vector<int> &v2id){
  int n = V.size();
  Graph res(n);
  for (int i = 0; i < n; i++) {
    v2component[V[i]] = bc.size();
    v2id[V[i]] = i;
    isVisited[V[i]] = 2;
  }
  for (int i = 0; i < n; i++) {
    int v = V[i];
    for (int j = g[v][0].next; j != g[v].end(); j=g[v][j].next) {
      int to = g[v][j].to;
      if(isVisited[to] != 2)continue;
      if(v > to)continue;
      res.AddEdge(i, v2id[to]);
    }
  }
  return res;
}

void BCDecomposition::dfs(int v, std::vector<int> &V){
  isVisited[v] = true;
  V.push_back(v);
  for (int i = g[v][0].next; i != g[v].end(); i=g[v][i].next) {
    int to = g[v][i].to;
    if(isVisited[to])continue;
    dfs(to, V);
  }
}

void BCDecomposition::decompose(){
  int n = g.size();
  std::vector<int> v2id(n);
  for (int i = 0; i < articulation.size(); i++) {
    isVisited[articulation[i]] = true;
  }  
  for (int i = 0; i < articulation.size(); i++) {
    int v = articulation[i];
    for (int j = g[v][0].next; j != g[v].end(); j=g[v][j].next) {
      int u = g[v][j].to;
      if(isVisited[u])continue;
      std::vector<int> V = {v};
      dfs(u, V);
      bc.push_back(GetInducedSubgraph(V, v2id));
    }
  }
}

bool checkPlanarity(Graph &g){
  int n = g.size(), m = 0;
  for (int i = 0; i < n; i++) {
    m += g[i].size();
  }
  if(m > 3*n - 3) return false;//necessary condition for planar graph
  BCDecomposition biconnect(g);
  return true;
}

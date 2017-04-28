#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<utility>

#include"graph.hpp"
typedef std::pair<int, int> pii;

int main(int argc, char *argv[]){
  if(argc != 2){
    std::cerr << "Error : The number of input file is not 2" <<std::endl;
    return 0;
  }
  
  std::ifstream ist(argv[1], std::ios::in);
  if(!ist){
    std::cerr << "can't open input file: " << argv[1] << std::endl;
    return 0;
  }
  int n;
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d", &n);
  Graph g(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    g.AddEdge(u, v);
  }
  //   for (int i = 0; i < n; i++) {
  //   g.AddEdge(i, edge(-1, -1, 1, -1));
  // }
  // while(getline(ist, tmp)){
  //   int u, v;
  //   sscanf(tmp.data(), "%d %d", &u, &v);
  //   g.AddEdge(u, edge(v, g[v].size(), g[u].size() + 1, g[u].size() - 1));
  //   g.AddEdge(v, edge(u, g[u].size() - 1, g[v].size() + 1, g[v].size() - 1));
  // }
  // for (int i = 0; i < n; i++) {
  //   g.AddEdge(i, edge(-1, -1, 1e9, g[i].size() - 1));
  // }


  
  std::vector<pii> ans = g.MIM();
  for (int i = 0; i < (int)ans.size(); i++) {
    std::cout << ans[i].first << " " << ans[i].second << std::endl;
  }
  return 0;
}

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>

using Graph = std::vector<std::vector<int> >;

int BruteForce(Graph &G, std::vector<std::vector<int> > &mat){
  int ans = 0, n = G.size();
  std::vector<int> V(n);
  for (long long int i = 1; i < (1LL<<n); i++) {
    int size = 0;
    for (int j = 0; j < n; j++) {
      if((i & (1LL<<j)))V[size++] = j;
    }
    bool isClique = true;
    for (int j = 0; isClique and j < size; j++) {
      for (int k = j + 1; isClique and k < size; k++) {
        if(mat[V[j]][V[k]] == 0) isClique = false;
      }
    }
    if(isClique)ans = std::max(ans, size);
  }
  return ans;
}

int MaxClique(Graph& G){
  int ans = 0, mini = 1e9, n = G.size(), m = 0;
  for (int i = 0; i < n; i++) {
    mini = std::min(mini, (int)G[i].size());
    m += G[i].size();
  }
  std::vector<std::vector<int> > mat(n, std::vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < G[i].size(); j++) {
      mat[i][G[i][j]] = 1;
    }
  }
  if(mini >= 2*sqrt(m)) return BruteForce(G, mat);
  std::vector<int> V(n);
  for (int i = 0; i < n; i++) {
    for (long long int j = 0; j < (1LL<<G[i].size()); j++) {
      int size = 0;
      for (int k = 0; k < G[i].size(); k++) {
        if((j & (1<<k)))V[size++] = G[i][k];
      }
      V[size++] = i;
      bool isClique = true;
      for (int x = 0; isClique and x < size; x++) {
        for (int y = x + 1; isClique and y < size; y++) {
          if(mat[V[x]][V[y]] == 0) isClique = false;
        }
      }
      if(isClique)ans = std::max(ans, size);
    }
  }
  return ans;
}

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
  int n, m;
  std::string tmp;
  getline(ist, tmp);
  sscanf(tmp.data(), "%d %d", &n, &m);
  Graph G(n);
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
  }
  std::cout << MaxClique(G) << std::endl;
  return 0;
}

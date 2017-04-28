#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<utility>

#include"checkPlanarity.hpp"
typedef std::pair<int, int> pii;
// typedef std::vector<std::vector<int> > Graph;

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
  Graph g(n, std::vector<int>());
  while(getline(ist, tmp)){
    int u, v;
    sscanf(tmp.data(), "%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  std::cout << "G is" << ((checkPlanarity(g))?"planar":"not planar") << std::endl;
  return 0;
}

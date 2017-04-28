#include<random>
#include<set>
#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<cstring>
typedef std::pair<int, int> pii;
typedef std::pair<int, pii> piii;
std::mt19937 mt(111);


void randomGraph(std::ofstream &output_file, int n){
  std::set<pii> edge;
  output_file << n << std::endl;
  while(edge.size() <= 2*n){
    pii add = pii(mt()%n, mt()%n);
    if(add.first == add.second)continue;
    pii rev = pii(add.second, add.first);
    if(edge.find(add) != edge.end() or
       edge.find(rev) != edge.end())continue;
    edge.insert(add);
  }
  for (auto e:edge) {
    output_file << e.first << " " << e.second << std::endl;
  }
}
void generate(std::ofstream &output_file, int mode){
  if(mode == 0){
    randomGraph(output_file, 6);
  }else if(mode == 1){
    randomGraph(output_file, 50);
  }else if(mode == 2){
    randomGraph(output_file, 70);
  }
}

int main(){
  std::string name;
  int case_size = 3;
  std::string case_name[] = {"small_",
                             "mid_",
                             "large_"};
  int case_cnt[] = {3, 3, 3};
  for (int i = 0; i < case_size; i++) {
    for (int j = 0; j < case_cnt[i]; j++) {
      char id[2];
      sprintf(id, "%02d", j);
      name = case_name[i] + id + ".in";
      std::cout << "generate " << name << std::endl;
      std::ofstream output_file(name.c_str());
      generate(output_file, i);
    }
  }
  return 0;
}

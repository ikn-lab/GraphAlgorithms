#include<iostream>
#include<vector>
#include<utility>
#include<list>
#include<set>
#include<cstring>
#include<algorithm>
#include"graph.hpp"

void FixedList::Remove(int pos){
  CheckList(pos);
  list[list[pos].next].prev = list[pos].prev;
  list[list[pos].prev].next = list[pos].next;
  is_in_list[pos] = false;
}

void FixedList::Add(int pos, int add){
  CheckList(pos);
  if(list[pos].prev == add)return;
  list[add].next = pos;
  list[add].prev = list[pos].prev;
  list[list[pos].prev].next = add;
  list[pos].prev = add;
  is_in_list[add] = true;
}

void FixedList::CheckList(int pos){
  if(is_in_list[pos] == false){
    std::cerr << "list do not include " << pos << std::endl;
    exit(1);
  }
}

void FixedList::Move(int from, int to){
  CheckList(from);
  Remove(from);
  is_in_list[from] = true;
  list[from].next = list[to].next;
  list[from].prev = to;
  
  list[list[to].next].prev = from;
  list[to].next = from;
}

void FixedList::connect(){
  for (int i = 0; i < n; i++) {
    list[i].next = i + 1;
    list[i].prev = i - 1;
    is_in_list[i] = true;
  }
}

void Graph::LexBfs(){
  int n = g.size();
  LexOrder.resize(n);
  LexOrderInverse.resize(n);
  FixedList que(2*n + 1);
  que.connect();
  std::vector<int> priority_array(n, n - 1);
  std::vector<int> count(n, 0), size(n, 0);
  std::vector<bool> deleted(n, false);  
  size[n - 1] = n;
  
  //begin = n, end = n + 1
  FixedList min_priority(n + 2, n, n + 1);
  min_priority.Add(n + 1, n - 1);
  
  for (int i = n - 1; i >= 0; i--) {
    //for (int i = 0; i < n; i++) {
    int v = que[min_priority[n].next].next - n;
    deleted[v] = true;
    
    que.Remove(v + n);
    size[priority_array[v]]--;
    
    if(size[priority_array[v]] == 0)
      min_priority.Remove(priority_array[v]);
    LexOrder[i] = v;
    LexOrderInverse[v] = i;

    for (int j = 0; j < (int)g[v].size(); j++) {
      if(deleted[g[v][j]])continue;
      int priority = priority_array[g[v][j]];
      count[priority]++;
      if(count[priority] == size[priority])
        count[priority] = 0;
    }
    for (int j = 0; j < (int)g[v].size(); j++) {
      int u = g[v][j];
      int priority = priority_array[u];
      if(deleted[u] or count[priority] == 0)continue;
      int move = priority - (size[priority] - count[priority]);
      que.Move(u + n, move);
      min_priority.Add(priority, move);
      priority_array[u] = move;
      size[priority]--, count[priority]--;
      size[move]++;
      if(size[priority] == 0) min_priority.Remove(priority);
    }
  }
  for (int i = 0; i < n; i++) {
    std::cout << "v:" << LexOrder[i] << std::endl;
  }
}

void Graph::AddEdge(int u, int v){
  g[u].emplace_back(v);
  g[v].emplace_back(u);
}

std::vector<pii> Graph::MIM(){
  int n = g.size();
  std::vector<pii> ans;
  std::cout << "LexBfs start" << std::endl;
  LexBfs();
  std::cout << "end" << std::endl;
  int mat[n][n];
  int original_mat[n][n];
  memset(mat, 0, sizeof(mat));
  memset(original_mat, 0, sizeof(original_mat));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < g[i].size(); j++) {
      int v = g[i][j];
      original_mat[i][v] = original_mat[v][i] = 1;
    }
  }
  for (int i = 0; i < n; i++) {
    int u = LexOrderInverse[i];
    for (int j = 0; j < g[i].size(); j++) {
      int v = LexOrderInverse[g[i][j]];
      mat[u][v] = mat[v][u] = 1;
    }
  }
  std::cout << "original" << std::endl;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << original_mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Lexicographical" << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::vector<pii> edge;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < g[i].size(); j++) {
      if(LexOrderInverse[i] < LexOrderInverse[g[i][j]]){
        edge.emplace_back(pii(LexOrderInverse[g[i][j]], LexOrderInverse[i]));
      }else {
        edge.emplace_back(pii(LexOrderInverse[i], LexOrderInverse[g[i][j]]));
      }
    }
  }
  sort(edge.begin(), edge.end());
  std::vector<bool> used(n, false);
  for (int i = 0; i < edge.size(); i++) {
    int u = LexOrder[edge[i].first], v = LexOrder[edge[i].second];
    if(used[u] == true or used[v] == true)continue;
    used[u] = used[v] = true;
    for (int j = 0; j < g[edge[i].first].size(); j++) {
      used[g[edge[i].first][j]] = true;
    }
    for (int j = 0; j < g[edge[i].second].size(); j++) {
      used[g[edge[i].second][j]] = true;
    }
    ans.emplace_back(edge[i]);
  }
  return ans;
}

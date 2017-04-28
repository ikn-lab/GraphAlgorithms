#include<string>
#include<list>
typedef std::pair<int, int> pii;

typedef struct cell{
  cell(){};
  cell(int n, int p):next(n), prev(p){};
  int next, prev;
}cell;


typedef class FixedList{
public:
  FixedList(int _n){n = _n, list.resize(n), is_in_list.resize(n, false);};
  FixedList(int _n, int s, int e){
    n = _n, list.resize(n), is_in_list.resize(n, false);
    list[s].next = e;
    list[e].prev = s;
    is_in_list[s] = is_in_list[e] = true;
  };
  
  void connect();
  void Remove(int pos);
  void Add(int pos, int add);
  void Move(int from, int to);
  cell& operator[](const int pos){return list[pos];};
private:
  int n;
  std::vector<cell> list;
  std::vector<bool> is_in_list;
  void CheckList(int pos);
}FixedList;

typedef class Graph{
public:
  Graph(int n){g.resize(n);}
  Graph(){};
  std::vector<pii> MIM();
  //void AddEdge(int from, edge e);
  void AddEdge(int u, int v);
  int size(){return g.size();};
  //std::vector<edge>& operator[](int v){return g[v];}
private:
  //std::vector<std::vector<edge> > g;
  std::vector<std::vector<int> > g;
  std::vector<int> LexOrder;
  std::vector<int> LexOrderInverse;
  void LexBfs();
  //void MoveBack(int to, int id);
}Graph;

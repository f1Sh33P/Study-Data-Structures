// minimum spanning tree (MST) -- Kruskal's algorithm
// 加边法，适合稀疏图
// 必须是无向连通网
#include <stdio.h>

#define MAXSIZE 100
#define INF 0x7fffffff

typedef char VexType;
typedef int EdgeType;

typedef struct {
  VexType vex[MAXSIZE];
  EdgeType arc[MAXSIZE][MAXSIZE];
  int vex_num, edge_num;
} MatGrph;

typedef struct {
  int begin, end, weight;
} Edge;

void create_graph(MatGrph *G) {
  G->vex_num  =  9;
  G->edge_num = 15;

  G->vex[0] = 'A'; G->vex[1] = 'B'; G->vex[2] = 'C';
  G->vex[3] = 'D'; G->vex[4] = 'E'; G->vex[5] = 'F';
  G->vex[6] = 'G'; G->vex[7] = 'H'; G->vex[8] = 'I';

  for (int i = 0; i < G->vex_num; i++)
    for (int j = 0; j < G->vex_num; j++)
      G->arc[i][j] = (i == j) ? 0 : INF;

  G->arc[0][1] = 10; G->arc[0][5] = 11;
  G->arc[1][2] = 18; G->arc[1][6] = 16; G->arc[1][8] = 12;
  G->arc[2][3] = 22; G->arc[2][8] =  8;
  G->arc[3][4] = 20; G->arc[3][6] = 24; G->arc[3][7] = 16; G->arc[3][8] = 21;
  G->arc[4][5] = 26; G->arc[4][7] =  7;
  G->arc[5][6] = 17;
  G->arc[6][7] = 19;

  for (int i = 0; i < G->vex_num; i++)
    for (int j = 0; j < G->vex_num; j++)
      G->arc[j][i] = G->arc[i][j];
}

/*
      A ─ 10 ─ B ─ 18 ─ C ──┐
      │        │ ╲      │   │
     11       16   12   8   │
      │        │      ╲ │   │
      F ─ 17 ─ G        I   22
      │        │ ╲      │   │
     26        │   24   21  │
      │        │      ╲ │   │
      E ── 7 ─ H ─ 16 ─ D ──┘
      │                 │
      └─────── 20 ──────┘
*/

void swap(Edge *edge, int i, int j) {
  Edge temp = edge[i];
  edge[i]   = edge[j];
  edge[j]   = temp;
}

void sortEdge(Edge *edge, int edge_num) {
  for (int i = 0; i < edge_num; i++)
    for (int j = i + 1; j < edge_num; j++)
      if (edge[i].weight > edge[j].weight)
        swap(edge, i, j);
}

int find(int *parent, int index) {
  // 使用 while 而不是 if
  while (parent[index] != index)
    index = parent[index];
  return index;
}

void kruskal(MatGrph G) {
  Edge edge[MAXSIZE];
  int k = 0;

  // #1 初始化
  for (int i = 0; i < G.vex_num; i++)
    for (int j = i + 1; j < G.vex_num; j++)
      if (G.arc[i][j] < INF) {
        edge[k].begin  = i;
        edge[k].end    = j;
        edge[k].weight = G.arc[i][j];
        k++;
      }

  // #2 排序
  sortEdge(edge, G.edge_num);

  // #3 标记
  int parent[MAXSIZE];
  for (int i = 0; i < G.vex_num; i++)
    parent[i] = i;

  for (int i = 0; i < G.edge_num; i++) {
    int m = find(parent, edge[i].begin);
    int n = find(parent, edge[i].end);

    // 如果不连通
    if (m != n) {
      parent[m] = n;
      printf("(%d, %d) %2d ", edge[i].begin, edge[i].end, edge[i].weight);
      printf("(%c, %c) %2d\n", G.vex[edge[i].begin], G.vex[edge[i].end], edge[i].weight);
    }
  }
}

int main(void) {
  MatGrph G;
  create_graph(&G);
  kruskal(G);
  return 0;
}
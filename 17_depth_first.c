// depth first search (DFS)
// 适用于图，不适用于网
// 代码以无向图为例
#include <stdio.h>

#define MAXSIZE 100

typedef char VexType;
typedef int EdgeType;

typedef struct {
  VexType vex[MAXSIZE];
  EdgeType arc[MAXSIZE][MAXSIZE];
  int vex_num, edge_num;
} MatGrph;

int visited[MAXSIZE];

void create_graph(MatGrph *G) {
  G->vex_num  =  9;
  G->edge_num = 15;

  G->vex[0] = 'A'; G->vex[1] = 'B'; G->vex[2] = 'C';
  G->vex[3] = 'D'; G->vex[4] = 'E'; G->vex[5] = 'F';
  G->vex[6] = 'G'; G->vex[7] = 'H'; G->vex[8] = 'I';

  for (int i = 0; i < G->vex_num; i++)
    for (int j = 0; j < G->vex_num; j++)
      G->arc[i][j] = 0;

  G->arc[0][1] = 1; G->arc[0][5] = 1;
  G->arc[1][2] = 1; G->arc[1][6] = 1; G->arc[1][8] = 1;
  G->arc[2][3] = 1; G->arc[2][8] = 1;
  G->arc[3][4] = 1; G->arc[3][6] = 1; G->arc[3][7] = 1; G->arc[3][8] = 1;
  G->arc[4][5] = 1; G->arc[4][7] = 1;
  G->arc[5][6] = 1;
  G->arc[6][7] = 1;

  for (int i = 0; i < G->vex_num; i++)
    for (int j = 0; j < G->vex_num; j++)
      G->arc[j][i] = G->arc[i][j];
}

/*
      A ─── B ─── C ─┐
      │     │ ╲   │  │
      │     │  ╲  │  │
      │     │   ╲ │  │
      F ─── G     I  │
      │     │ ╲   │  │
      │     │  ╲  │  │
      │     │   ╲ │  │
      E ─── H ─── D ─┘
      └───────────┘
*/

void dfs(MatGrph G, int i) {
  visited[i] = 1;

  printf("%c ", G.vex[i]);

  for (int j = 0; j < G.vex_num; j++)
    if (G.arc[i][j] == 1 && visited[j] == 0)
      dfs(G, j);
}

int main(void) {
  MatGrph G;

  create_graph(&G);

  for (int i = 0; i < G.vex_num; i++) visited[i] = 0;

  dfs(G, 0);
  return 0;
}
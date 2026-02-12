// minimum spanning tree (MST) -- Prim's algorithm
// 加点法，适合稠密图
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

void prim(MatGrph *G) {
  int i, j, k;
  int min;

  // #1 初始化
  // weight 数组保存当前生成树到各个顶点的最小距离。如果 weight[i] == 0，说明顶点 i 已经在生成树中了
  int weight[MAXSIZE];

  // vex_index 数组保存对应顶点的前驱。例如 vex_index[1] = 0，表示顶点 B 的前驱是 A，进而表示以 A 和 B 为顶点的边
  int vex_index[MAXSIZE];

  // 从顶点 A 出发
  weight[0] = 0;
  vex_index[0] = 0;

  // 初始化顶点 A 以外的其他顶点
  for (i = 1; i < G->vex_num; i++) {
    weight[i] = G->arc[0][i];
    vex_index[i] = 0;
  }

  // #2 寻找
  // 最小生成树有 vex_num 个顶点，vertex_num - 1 条边，因此循环 vex_num - 1 次，每次循环找到一条边
  for (i = 1; i < G->vex_num; i++) {
    min = INF;
    j = k = 0;

    // 寻找离当前生成树最近的顶点
    while (j++ < G->vex_num)
      if (weight[j] != 0 && weight[j] < min) { // j 用于比较和迭代，k 用于记录
        min = weight[j];
        k = j;
      }

    // 输出
    printf("(%d, %d) ", vex_index[k], k);
    printf("(%c, %c)\n", G->vex[vex_index[k]], G->vex[k]);

    // 将找到的顶点加入生成树
    weight[k] = 0;

    // 更新
    for (j = 0; j < G->vex_num; j++)
      if (weight[j] != 0 && G->arc[k][j] < weight[j]) {
        weight[j] = G->arc[k][j]; // 更新权值
        vex_index[j] = k;         // 更新前驱
      }
  }
}

int main(void) {
  MatGrph G;
  create_graph(&G);
  prim(&G);
  return 0;
}
// shortest path -- Floyd–Warshall algorithm
// 适用于网，可以处理负权边
// 代码以无向网为例
#include <stdio.h>

#define MAXSIZE 100
#define INF 0x3f3f3f3f

typedef int VexType;
typedef int EdgeType;

typedef struct {
  VexType vex[MAXSIZE];
  EdgeType arc[MAXSIZE][MAXSIZE];
  int vex_num, edge_num;
} Graph;

void create(Graph *G) {
  G->vex_num  =  9;
  G->edge_num = 16;

  for (int i = 0; i < G->vex_num; i++) {
    G->vex[i] = i;
    for (int j = 0; j < G->vex_num; j++)
      G->arc[i][j] = (i == j) ? 0 : INF;
  }

  G->arc[0][1] = 1; G->arc[0][2] = 5;
  G->arc[1][2] = 3; G->arc[1][3] = 7; G->arc[1][4] = 5;
  G->arc[2][4] = 1; G->arc[2][5] = 7;
  G->arc[3][4] = 2; G->arc[3][6] = 3;
  G->arc[4][5] = 3; G->arc[4][6] = 6; G->arc[4][7] = 9;
  G->arc[5][7] = 5;
  G->arc[6][7] = 2; G->arc[6][8] = 7;
  G->arc[7][8] = 4;

  for (int i = 0; i < G->vex_num; i++)
    for (int j = i + 1; j < G->vex_num; j++)
      G->arc[j][i] = G->arc[i][j];
}

/*
              [0]
             ╱   ╲
            1     5
           ╱       ╲
         [1] ─ 3 ─ [2]
        ╱   ╲     ╱   ╲
       7     5   1     7
      ╱       ╲ ╱       ╲
    [3] ─ 2 ─ [4] ─ 3 ─ [5]
      ╲       ╱ ╲       ╱
       3     6   9     5
        ╲   ╱     ╲   ╱
         [6] ─ 2 ─ [7]
           ╲       ╱
            7     4
             ╲   ╱
              [8]
*/

void print_result(int dist[][MAXSIZE], int path[][MAXSIZE], int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      printf("Shortest distance from [%d] to [%d] is %2d, path: [%d]",
             i, j, dist[i][j], i);

      int curr = path[i][j];

      while (curr != j) {
        printf(" -> [%d]", curr);
        curr = path[curr][j];
      }
      printf(" -> [%d]\n", j);
    }
    printf("\n");
  }
}

void floyd(Graph *G) {
  int path[MAXSIZE][MAXSIZE];
  int dist[MAXSIZE][MAXSIZE];

  for (int i = 0; i < G->vex_num; i++)
    for (int j = 0; j < G->vex_num; j++) {
      dist[i][j] = G->arc[i][j];
      path[i][j] = j; // 初始化 path 指向终点
    }

  // i 代表起始顶点，j 代表终止顶点，k 代表中间顶点，必须在最外层
  // 第二、三层可以先 j 后 i，但先 i 后 j 有利于 CPU 连续访问
  for (int k = 0; k < G->vex_num; k++)
    for (int i = 0; i < G->vex_num; i++)
      for (int j = 0; j < G->vex_num; j++)
        if (dist[i][k] != INF && dist[k][j] != INF &&
            dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          path[i][j] = path[i][k];
        }

  print_result(dist, path, G->vex_num);
}

int main(void) {
  Graph G;
  create(&G);
  floyd(&G);
  return 0;
}
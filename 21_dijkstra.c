// shortest path -- Dijkstra's algorithm
// 适用于网，无法处理负权边
// 代码以无向网为例
#include <stdio.h>

#define MAXSIZE 100
#define INF 0x10000

typedef int VexType;
typedef int EdgeType;

typedef struct {
  VexType vex[MAXSIZE];
  EdgeType arc[MAXSIZE][MAXSIZE];
  int vex_num, edge_num;
} MatGraph;

void create(MatGraph *G) {
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

// 寻找当前未访问顶点中离起点最近的顶点
int choose(int distance[], int found[], int vex_num) {
  int min = INF;
  int minPos = -1;
  for (int i = 0; i < vex_num; i++)
    if (distance[i] < min && found[i] == 0) {
      min = distance[i];
      minPos = i;
    }
  return minPos;
}

void dijkstra(MatGraph G, int begin) {
  int found[MAXSIZE];    // found[i] = 1 表示起点到 i 的最短路径已确定
  int path[MAXSIZE];     // path[i] 记录顶点 i 的前驱，用于回溯路径
  int distance[MAXSIZE]; // distance[i] 记录当前从起点到 i 的最短距离

  // 初始化
  for (int i = 0; i < G.vex_num; i++) {
    found[i] = 0;
    path[i] = -1;
    distance[i] = G.arc[begin][i];
  }
  found[begin] = 1;
  distance[begin] = 0;

  // 主循环
  int next;
  for (int i = 0; i < G.vex_num - 1; i++) {
    next = choose(distance, found, G.vex_num);
    printf("%d ", next);
    found[next] = 1;

    // 检查经过 next 到 j 是否比直接到 j 更近
    for (int j = 0; j < G.vex_num; j++)
      if (found[j] == 0)
        if (distance[next] + G.arc[next][j] < distance[j]) {
          distance[j] = distance[next] + G.arc[next][j];
          path[j] = next;
        }
  }
  printf("\n");

  // 输出
  for (int i = 0; i < G.vex_num; i++)
    if (i != begin) {
      printf("Shortest distance from [%d] to [%d] is %2d, ", begin, i, distance[i]);
      printf("and the corresponding path is: [%d] <- ", i);

      int j = i;
      while (path[j] != -1) {
        printf("[%d] <- ", path[j]);
        j = path[j];
      }

      printf("[%d]\n", begin);
    }
}

int main(void) {
  MatGraph G;
  int begin = 0;

  create(&G);

  dijkstra(G, begin);
  return 0;
}
// critical path method (CPM)
// 必须是有向无环图（网）
// 代码以有向无环网为例
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define INF 0x7fffffff

typedef int VexType;
typedef int EdgeType;

typedef struct {
  VexType vex[MAXSIZE];
  EdgeType arc[MAXSIZE][MAXSIZE];
  int vex_num, edge_num;
} MatGraph;

typedef struct edgeNode {
  int data, weight;
  struct edgeNode *next;
} EdgeNode;

typedef struct {
  int in;
  VexType data;
  EdgeNode *head;
} VexNode;

typedef struct {
  VexNode list[MAXSIZE];
  int vex_num, edge_num;
} AdjListGraph;

/*
list[0]: VexNode -> EdgeNode -> EdgeNode -> ...
list[1]: VexNode -> EdgeNode -> EdgeNode -> ...
list[2]: VexNode -> EdgeNode -> EdgeNode -> ...
...
*/

void createGraph(MatGraph *G) {
  G->vex_num  = 10;
  G->edge_num = 13;

  for (int i = 0; i < G->vex_num; i++) {
    G->vex[i] = i;
    for (int j = 0; j < G->vex_num; j++)
      G->arc[i][j] = (i == j) ? 0 : INF;
  }

  G->arc[0][1] = 3; G->arc[0][2] = 4;
  G->arc[1][3] = 5; G->arc[1][4] = 6;
  G->arc[2][3] = 8; G->arc[2][5] = 7;
  G->arc[3][4] = 3;
  G->arc[4][6] = 9; G->arc[4][7] = 4;
  G->arc[5][7] = 6;
  G->arc[6][9] = 2;
  G->arc[7][8] = 5;
  G->arc[8][9] = 3;
}

/*
                 ┌─────────── 6 ───────────┐
                 │                         ▼
      ┌── 3 ──► [1] ── 5 ──► [3] ── 3 ──► [4] ──── 9 ────► [6] ──────┐
      │                       ▲            │                         │
      │                       │            │                         │
     [0]                      │            4                         2
      │          ┌──── 8 ─────┘            │                         │
      │          │                         │                         │
      │          │                         ▼                         ▼
      └── 4 ──► [2] ── 7 ──► [5] ── 6 ──► [7] ── 5 ──► [8] ── 3 ──► [9]
*/

void createAdjListGraph(MatGraph *G, AdjListGraph **ALG) {
  // 初始化 ALG，共五项内容
  *ALG = (AdjListGraph *)malloc(sizeof(AdjListGraph));
  (*ALG)->vex_num  = G->vex_num;
  (*ALG)->edge_num = G->edge_num;
  for (int i = 0; i < G->vex_num; i++) {
    (*ALG)->list[i].in = 0;
    (*ALG)->list[i].data = G->vex[i];
    (*ALG)->list[i].head = NULL;
  }

  // 初始化 EdgeNode
  for (int i = 0; i < G->vex_num; i++)
    for (int j = 0; j < G->vex_num; j++)
      if (G->arc[i][j] != 0 && G->arc[i][j] < INF) {
        EdgeNode *e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->data = j;
        e->weight = G->arc[i][j];
        e->next = (*ALG)->list[i].head;
        (*ALG)->list[i].head = e;
        (*ALG)->list[j].in++;
      }
}

void criticalPath(AdjListGraph *ALG) {
  EdgeNode *e;
  int curr, k;

  int etv[MAXSIZE];               // earliest time of vertex，正向推导取较大值
  int ltv[MAXSIZE];               // latest time of vertex，逆向推导取较小值
  int top1 = -1, stack1[MAXSIZE]; // 用于拓扑排序
  int top2 = -1, stack2[MAXSIZE]; // 用于计算 ltv

  // 入栈 1，并初始化 etv
  for (int i = 0; i < ALG->vex_num; i++) {
    if (ALG->list[i].in == 0) stack1[++top1] = i;
    etv[i] = 0;
  }

  // 出栈 1、入栈 2，并计算 etv
  printf("%18s", "Topological sort: ");
  while (top1 != -1) {
    curr = stack1[top1--];
    stack2[++top2] = curr;
    printf("[%d] -> ", ALG->list[curr].data);

    // 将 list[curr] 这一条链表走完
    for (e = ALG->list[curr].head; e != NULL; e = e->next) {
      k = e->data;
      if (--ALG->list[k].in == 0)
        stack1[++top1] = k;
      if (etv[curr] + e->weight > etv[k])
        etv[k] = etv[curr] + e->weight;
    }
  }
  printf("end\n");

  // 输出 etv
  printf("%18s", "ETV: ");
  for (int i = 0; i < ALG->vex_num; i++)
    printf("%3d -> ", etv[i]);
  printf("end\n");

  // 初始化 ltv
  for (int i = 0; i < ALG->vex_num; i++)
    ltv[i] = etv[ALG->vex_num - 1];

  // 出栈 2，并计算 ltv
  while (top2 != -1) {
    curr = stack2[top2--];

    // 将 list[curr] 这一条链表走完
    for (e = ALG->list[curr].head; e != NULL; e = e->next) {
      k = e->data;
      if (etv[k] - e->weight < ltv[curr])
        ltv[curr] = etv[k] - e->weight;
    }
  }

  // 输出 ltv
  printf("%18s", "LTV: ");
  for (int i = 0; i < ALG->vex_num; i++)
    printf("%3d -> ", ltv[i]);
  printf("end\n");

  // 输出 critical path
  printf("%18s", "Critical path: ");
  for (int i = 0; i < ALG->vex_num; i++)
    if (etv[i] == ltv[i]) printf("[%d] -> ", i);
  printf("end\n");
}

int main(void) {
  MatGraph G;
  AdjListGraph *ALG;

  createGraph(&G);
  createAdjListGraph(&G, &ALG);

  criticalPath(ALG);
  return 0;
}
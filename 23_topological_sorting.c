// topological sorting
// 必须是有向无环图（网）
// 代码以有向无环图为例
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int VexType;
typedef int EdgeType;

// adjacency matrix
typedef struct {
  VexType vex[MAXSIZE];
  EdgeType arc[MAXSIZE][MAXSIZE];
  int vex_num, edge_num;
} MatGraph;

// adjacency list
typedef struct edgeNode {
  int data;
  struct edgeNode *next;
} EdgeNode;

typedef struct {
  int in; // in-degree
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
  G->vex_num  = 14;
  G->edge_num = 20;

  for (int i = 0; i < G->vex_num; i++) {
    G->vex[i] = i;
    for (int j = 0; j < G->vex_num; j++)
      G->arc[i][j] = 0;
  }

  G->arc[0][4]   = 1; G->arc[0][5]  = 1; G->arc[0][11] = 1;
  G->arc[1][2]   = 1; G->arc[1][4]  = 1; G->arc[1][8]  = 1;
  G->arc[2][5]   = 1; G->arc[2][6]  = 1; G->arc[2][9]  = 1;
  G->arc[3][2]   = 1; G->arc[3][13] = 1;
  G->arc[4][7]   = 1;
  G->arc[5][8]   = 1; G->arc[5][12] = 1;
  G->arc[6][5]   = 1;
  G->arc[8][7]   = 1;
  G->arc[9][10]  = 1;
  G->arc[10][13] = 1;
  G->arc[12][9]  = 1;
}

/*
      ┌───────── [1] ──────────────► [8] ──────────┐
      │           │                   ▲            │
      │           ▼                   └┐           ▼
      │          [4] ──────────────────┼────────► [7]
      │           ▲                   ┌┘
      │           │                   │
      │          [0] ────► [11]       │
      │           │                   │
      │           ▼                   │
      │     ┌──► [5] ───┬─────────────┘
      │     │     ▲     │
      │     │     │     └───► [12] ───┐
      │     │     │                   │
      ▼     │     └┐                  ▼
     [2] ───┼──────┼───────────────► [9] 
      ▲     │     ┌┘                  │
      │     ▼     │                   │
      │    [6] ───┘                   │
      │                               ▼
      └─── [3] ──────► [13] ◄────── [10]
*/

// adjacency matrix to adjacency list
void createAdjListGraph(MatGraph *G, AdjListGraph **ALG) {
  // 传入的 ALG 是一个二重指针
  // 初始化 ALG，共五项内容
  *ALG = (AdjListGraph *)malloc(sizeof(AdjListGraph));
  (*ALG)->vex_num  = G->vex_num;
  (*ALG)->edge_num = G->edge_num;
  for (int i = 0; i < G->vex_num; i++) {
    // 初始化 list 数组，即初始化 VexNode
    (*ALG)->list[i].in = 0;
    (*ALG)->list[i].data = G->vex[i];
    (*ALG)->list[i].head = NULL;
  }

  // 初始化 EdgeNode，使用头插法
  for (int i = 0; i < G->vex_num; i++)
    for (int j = 0; j < G->vex_num; j++)
      if (G->arc[i][j] == 1) {
        EdgeNode *e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->data = j;
        e->next = (*ALG)->list[i].head;
        (*ALG)->list[i].head = e;
        (*ALG)->list[j].in++;
      }
}

void topologicalSort(AdjListGraph *ALG) {
  int top = -1;
  int stack[MAXSIZE];

  // push
  for (int i = 0; i < ALG->vex_num; i++)
    if (ALG->list[i].in == 0) stack[++top] = i;

  // pop
  while (top != -1) {
    int curr = stack[top--];
    printf("[%d] -> ", ALG->list[curr].data);

    // 将 list[curr] 这一条链表走完
    for (EdgeNode *e = ALG->list[curr].head; e != NULL; e = e->next) {
      int k = e->data;
      if (--ALG->list[k].in == 0) stack[++top] = k;
    }
  }
}

int main(void) {
  MatGraph G;
  AdjListGraph *ALG;

  createGraph(&G);
  createAdjListGraph(&G, &ALG);

  topologicalSort(ALG);
  printf("\b\b\b\b    \n");
  return 0;
}
// 队列的顺序结构实现 -- 循环队列
// 表面上使用 malloc 进行动态内存分配，实际上仍是：#1 开辟定长的存储空间，#2 使用数组进行管理
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct {
  ElemType *data;
  int front;
  int rear;
} Queue;

// initialize
Queue *initQueue() {
  Queue *Q = (Queue *)malloc(sizeof(Queue));
  Q->data = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
  Q->front = 0;
  Q->rear = 0;
  return Q;
}

// 入队
int enqueue(Queue *Q, ElemType e) {
  // 在 Q->rear + 1 == Q->front 的基础上进行修正
  if ((Q->rear + 1) % MAXSIZE == Q->front) {
    printf("Full\n");
    return 0;
  }
  Q->data[Q->rear] = e;
  Q->rear = (Q->rear + 1) % MAXSIZE; // 这样设计的循环队列，实际上只能存 MAXSIZE - 1 个元素
  return 1;
}

// 出队
int dequeue(Queue *Q, ElemType *e) {
  if (Q->front == Q->rear) {
    printf("Empty\n");
    return 0;
  }
  *e = Q->data[Q->front];
  Q->front = (Q->front + 1) % MAXSIZE;
  return 1;
}

int main(void) {
  return 0;
}
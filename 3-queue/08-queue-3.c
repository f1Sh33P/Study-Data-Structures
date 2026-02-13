// 队列的链式结构实现
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct queueNode {
  ElemType data;
  struct queueNode *next;
} QueueNode;

typedef struct {
  QueueNode *front, *rear;
} Queue;

// initialize
Queue *initQueue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
  node->data = 0;
  node->next = NULL;
  q->front = node;
  q->rear = node;
  return q;
}

// 判断队列是否为空
int isEmpty(Queue *Q) {
  return Q->front == Q->rear;
}

// 入队 -- 尾插法
void enqueue(Queue *Q, ElemType e) {
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
  node->data = e;
  node->next = NULL;
  Q->rear->next = node;
  Q->rear = node;
}

// 出队 -- 删除头结点的后继
int dequeue(Queue *Q, ElemType *e) {
  QueueNode *node = Q->front->next;
  *e = node->data;
  Q->front->next = node->next;
  if (Q->rear == node)
    Q->rear = Q->front;
  free(node);
  return 1;
}

// 获取队头元素
ElemType getFront(Queue *Q) {
  if (isEmpty(Q)) {
    printf("Empty\n");
    return 0;
  }
  return Q->front->next->data;
}

int main(void) {
  Queue *q = initQueue();
  ElemType e;

  enqueue(q, 10);
  enqueue(q, 20);
  enqueue(q, 30);
  enqueue(q, 40);
  enqueue(q, 50);

  dequeue(q, &e);
  printf("%d\n", e);

  dequeue(q, &e);
  printf("%d\n", e);

  printf("%d\n", getFront(q));
  return 0;
}
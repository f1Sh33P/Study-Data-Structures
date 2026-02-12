// 层序遍历 -- 队列
#include <stdio.h>
#include <stdlib.h>

// 树
typedef char ElemType;

typedef struct treeNode {
  ElemType data;
  struct treeNode *lchild, *rchild;
} TreeNode, *BiTree;

// 队列
typedef BiTree QueueElemType;

typedef struct queueNode {
  QueueElemType data;
  struct queueNode *next;
} QueueNode;

typedef struct {
  QueueNode *front, *rear;
} Queue;

char str[] = "ABDH#K###E##CFI###G#J##";
int idx = 0;

/*
             ┌─────── A ───────┐
             │                 │
        ┌─── B ───┐       ┌─── C ───┐
        │         │       │         │
     ┌─ D         E    ┌─ F         G ─┐
     │                 │               │
     H                 I               J
     └──┐
        K
*/

void createTree(BiTree *T) {
  ElemType ch = str[idx++];
  if (ch == '#') *T = NULL;
  else {
    *T = (BiTree)malloc(sizeof(TreeNode));
    (*T)->data = ch;
    createTree(&(*T)->lchild);
    createTree(&(*T)->rchild);
  }
}

Queue *initQueue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
  node->data = NULL;
  node->next = NULL;
  q->front = q->rear = node;
  return q;
}

int isEmpty(Queue *q) {
  return (q->front == q->rear);
}

void enqueue(Queue *q, QueueElemType e) {
  QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
  node->data = e;
  node->next = NULL;
  q->rear->next = node;
  q->rear = node;
}

int dequeue(Queue *q, QueueElemType *e) {
  QueueNode *node = q->front->next;
  *e = node->data;
  q->front->next = node->next;
  if (q->rear == node) q->rear = q->front;
  free(node);
  return 1;
}

int queueSize(Queue *q) {
  int count = 0;
  QueueNode *p = q->front->next; 
  while (p) {
    count++;
    p = p->next;
  }
  return count;
}

int maxDepth(TreeNode *root) {
  if (!root) return 0;
  int depth = 0;
  Queue *q = initQueue();

  enqueue(q, root);
  while (!isEmpty(q)) {
    int count = queueSize(q);

    while (count > 0) {
      TreeNode *curr;
      dequeue(q, &curr);
      if (curr->lchild) enqueue(q, curr->lchild);
      if (curr->rchild) enqueue(q, curr->rchild);
      count--;
    }

    depth++;
  }
  return depth;
}

int main(void) {
  BiTree T;

  createTree(&T);

  printf("%d\n", maxDepth(T));
  return 0;
}
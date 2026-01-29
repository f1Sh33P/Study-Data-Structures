// 双向链表
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node {
  ElemType data;
  struct node *prev, *next;
} Node;

// initialize
Node *initList() {
  Node *head = (Node *)malloc(sizeof(Node));
  head->data = 0;
  head->prev = NULL;
  head->next = NULL;
  return head;
}

// 头插法
int insertHead(Node *L, ElemType e) {
  Node *p = (Node *)malloc(sizeof(Node));
  p->data = e;
  p->prev = L;
  p->next = L->next;
  if (L->next) L->next->prev = p;
  L->next = p;
  return 1;
}

// traversal
void listNode(Node *L) {
  for (Node *p = L->next; p; p = p->next) printf("%d ", p->data);
  printf("\n");
}

// 获取尾结点
Node *getTail(Node *L) {
  Node *p = L;
  while (p->next) p = p->next;
  return p;
}

// 尾插法 -- 返回新的尾结点，方便连续插入
Node *insertTail(Node *tail, ElemType e) {
  Node *p = (Node *)malloc(sizeof(Node));
  p->data = e;
  p->prev = tail;
  p->next = NULL;
  tail->next = p;
  return p;
}

// 在指定位置插入结点
int insertNode(Node *L, int pos, ElemType e) {
  if (pos < 1) return 0;
  Node *p = L;

  for (int i = 0; i < pos - 1; i++) {
    p = p->next;
    if (!p) return 0;
  }

  Node *q = (Node *)malloc(sizeof(Node));
  q->data = e;
  q->prev = p;
  q->next = p->next;
  p->next->prev = q;
  p->next = q;
  return 1;
}

// 删除指定位置的结点
int deleteNode(Node *L, int pos) {
  if (pos < 1) return 0;
  Node *p = L; // p 存放 pos 的前驱

  for (int i = 0; i < pos - 1; i++) {
    p = p->next;
    if (!p) return 0;
  }

  if (!p->next) {
    printf("Position error\n");
    return 0;
  }

  Node *q = p->next; // q 存放 pos 本身
  p->next = q->next; // 让 pos 的前驱指向 pos 的后继
  q->next->prev = p; // 让 pos 的后继指向 pos 的前驱
  free(q);           // 释放 pos
  return 1;
}

int main(void) {
  Node *list = initList();

  insertHead(list, 10);
  insertHead(list, 20);
  insertHead(list, 30);
  listNode(list);

  Node *tail = getTail(list);
  tail = insertTail(tail, -10);
  tail = insertTail(tail, 20);

  printf("Original list: ");
  listNode(list);

  insertNode(list, 2, 999);
  printf("After insert 999 at 2: ");
  listNode(list);

  deleteNode(list, 2);
  printf("After delete at 2: ");
  listNode(list);
  return 0;
}
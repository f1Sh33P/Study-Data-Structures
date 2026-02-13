// 栈的链式结构实现
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct stack {
  ElemType data;
  struct stack *next;
} Stack;

// initialize
Stack *initStack() {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->data = 0;
  s->next = NULL; // s->next 作为栈顶
  return s;       // 返回头结点
}

// 判断栈是否为空
int isEmpty(Stack *s) {
  if (s->next == NULL) {
    printf("Empty\n");
    return 1;
  } else
    return 0;
}

// 进栈 -- 头插法
int push(Stack *s, ElemType e) {
  Stack *p = (Stack *)malloc(sizeof(Stack));
  p->data = e;
  p->next = s->next;
  s->next = p;
  return 1;
}

// 出栈 -- 删除头结点的后继
int pop(Stack *s, ElemType *e) {
  if (s->next == NULL) {
    printf("Empty\n");
    return 0;
  }
  *e = s->next->data;

  Stack *q = s->next;
  s->next = q->next;
  free(q);
  return 1;
}

// 获取栈顶元素
int getTop(Stack *s, ElemType *e) {
  if (!s->next) {
    printf("Empty\n");
    return 0;
  }
  *e = s->next->data;
  return 1;
}

int main(void) {
  Stack *s = initStack();
  ElemType e;

  push(s, 10);
  push(s, 20);
  push(s, 30);
  
  pop(s, &e);
  printf("%d\n", e);

  getTop(s, &e);
  printf("%d\n", e);
  return 0;
}
// 栈的顺序结构实现
// 表面上使用 malloc 进行动态内存分配，实际上仍是：#1 开辟定长的存储空间，#2 使用数组进行管理
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct {
  ElemType *data;
  int top;
} Stack;

// initialize
Stack *initStack() {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->data = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
  s->top = -1;
  return s;
}

// 进栈
int push(Stack *s, ElemType e) {
  if (s->top == MAXSIZE - 1) {
    printf("Full\n");
    return 0;
  }
  s->data[++s->top] = e;
  return 1;
}

// 出栈
int pop(Stack *s, ElemType *e) {
  if (s->top == -1) {
    printf("Empty\n");
    return 0;
  }
  *e = s->data[s->top--];
  return 1;
}

// 获取栈顶元素
int getTop(Stack *s, ElemType *e) {
  if (s->top == -1) {
    printf("Empty\n");
    return 0;
  }
  *e = s->data[s->top];
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
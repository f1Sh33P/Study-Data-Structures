// 栈的顺序结构实现
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct {
  ElemType data[MAXSIZE];
  int top; // 栈顶元素的下标
} Stack;

// initialize
void initStack(Stack *s) {
  s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack *s) {
  if (s->top == -1) {
    printf("Empty\n");
    return 1;
  } else
    return 0;
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
  Stack s;
  ElemType e;

  initStack(&s);
  push(&s, 10);
  push(&s, 20);
  push(&s, 30);

  pop(&s, &e);
  printf("%d\n", e);

  getTop(&s, &e);
  printf("%d\n", e);
  return 0;
}
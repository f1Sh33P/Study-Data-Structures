// 栈的链式结构实现 -- 二重指针
// 与 stack_3.c 进行对比
// 过去链表的初始化 (a) 只使用一重指针，但返回值是地址
// 实际上也可以 (b) 使用二重指针作为参数传递，返回 void 或 int
// 就是不能 (c) 直接将一重指针作为参数传递，返回 void
// 这是因为，使用指针相当于一次抽象：#1 管理链表需要一次抽象，#2 调用函数需要再次抽象
// 函数不再像个弱小的「求职者」把结果递回来，而像个「修理工」直接进入现场解决问题
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct stack {
  ElemType data;
  struct stack *next;
} Stack;

int initStack(Stack **s) {
  *s = (Stack *)malloc(sizeof(Stack));
  (*s)->data = 0;
  (*s)->next = NULL;
  return 1;
}

int main(void) {
  Stack *s;
  initStack(&s);
  return 0;
}
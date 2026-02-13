// 前序遍历 -- 非递归
#include <stdio.h>
#include <stdlib.h>

// 树
typedef char ElemType;

typedef struct treeNode {
  ElemType data;
  struct treeNode *lchild;
  struct treeNode *rchild;
} TreeNode, *BiTree;

// 栈
typedef BiTree StackElemType;

typedef struct stack {
  StackElemType data;
  struct stack *next;
} Stack;

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

Stack *initStack() {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->data = NULL;
  s->next = NULL; 
  return s;
}

int isEmpty(Stack *s) {
  return !s->next;
}

int push(Stack *s, StackElemType e) {
  Stack *p = (Stack *)malloc(sizeof(Stack));
  p->data = e;
  p->next = s->next;
  s->next = p;
  return 1;
}

int pop(Stack *s, StackElemType *e) {
  if (isEmpty(s)) return 0;
  Stack *q = s->next;
  *e = q->data;
  s->next = q->next;
  free(q);
  return 1;
}

void iterPreOrder(Stack *s, BiTree T) {
  while (T || !isEmpty(s)) {
    // 只要当前结点不为空，输出根结点并将根入栈，以便之后找右孩子
    while (T) {
      printf("%c ", T->data);
      push(s, T);
      T = T->lchild;
    }

    // 左边到头了，将根出栈，转向右子树
    pop(s, &T);
    T = T->rchild;
  }
  printf("\n");
}

int main(void) {
  BiTree T;
  Stack *s = initStack();

  createTree(&T);

  iterPreOrder(s, T);
  return 0;
}
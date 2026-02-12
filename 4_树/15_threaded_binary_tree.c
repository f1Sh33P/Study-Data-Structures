// 线索二叉树
// 不理解递归，就不理解函数的核心思想：对内隐藏细节，对外暴露接口
// 理解递归的关键不在推演，而在于：#1 递归的出口，#2 递归的位置，#3 递归的边界
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct threadNode {
  ElemType data;
  struct threadNode *left_child, *right_child;
  int left_tag, right_tag; // tag = 0 表示结点，tag = 1 表示线索
} ThreadNode, *ThreadTree;

/*
            ┌─────── A ───────┐
            │                 │
       ┌─── B ───┐       ┌─── C ───┐
       │         │       │         │
    ┌─ D ─┐   ┌─ E       F         G
    │     │   │
    H     I   J
*/

char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;
ThreadTree prev; // 记录上次访问的结点

void createTree(ThreadTree *T) {
  ElemType ch = str[idx++];
  if (ch == '#') *T = NULL; // 出口
  else {
    *T = (ThreadTree)malloc(sizeof(ThreadNode));
    (*T)->data = ch;

    createTree(&(*T)->left_child);
    if ((*T)->left_child)
      (*T)->left_tag = 0;

    createTree(&(*T)->right_child);
    if ((*T)->right_child)
      (*T)->right_tag = 0;
  }
}

// 线索化
void threading(ThreadTree T) {
  if (T) {
    // #1
    threading(T->left_child);

    // #2
    if (!T->left_child) {
      T->left_tag = 1;
      T->left_child = prev;
    }

    // #3
    if (!prev->right_child) {
      prev->right_tag = 1;
      prev->right_child = T;
    }

    // #4
    prev = T;

    // #5
    threading(T->right_child);
  }
}

// 完善线索化，并添加头结点
void inOrderThreading(ThreadTree *head, ThreadTree T) {
  *head = (ThreadTree)malloc(sizeof(ThreadNode));
  (*head)->left_tag = 0;
  (*head)->right_tag = 1;
  (*head)->right_child = *head;

  if (!T) (*head)->left_child = *head;

  // 大部分内容是对 threading() 函数边界的完善
  else {
    // 头结点的左孩子指向二叉树的根
    (*head)->left_child = T;
    prev = *head;
    threading(T);
    prev->right_tag = 1;
    prev->right_child = *head;   // 最后一个结点的右孩子指向头结点
    (*head)->right_child = prev; // 头结点的右孩子指向最后一个结点
  }
}

// 根据线索中序遍历 -- 非递归
void inOrder(ThreadTree T) {
  ThreadTree curr = T->left_child;

  while (curr != T) {
    while (curr->left_tag == 0) curr = curr->left_child;
    printf("%c ", curr->data);

    while (curr->right_tag == 1 && curr->right_child != T) {
      curr = curr->right_child;
      printf("%c ", curr->data);
    }

    curr = curr->right_child;
  }
  printf("\n");
}

int main(void) {
  ThreadTree T, head;

  createTree(&T);

  inOrderThreading(&head, T);

  inOrder(head);
  return 0;
}
// 二叉树的链式结构实现
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct treeNode {
  ElemType data;
  struct treeNode *lchild, *rchild;
} TreeNode, *BiTree;

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

// 初始化 -- 二重指针
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

// 初始化 -- 一重指针
BiTree create() {
  ElemType ch = str[idx++];
  if (ch == '#') return NULL;
  BiTree T = (BiTree)malloc(sizeof(TreeNode));
  T->data = ch;
  T->lchild = create();
  T->rchild = create();
  return T;
}

// 前序遍历
void preOrder(BiTree T) {
  if (!T) return;
  printf("%c ", T->data);
  preOrder(T->lchild);
  preOrder(T->rchild);
}

// 中序遍历
void inOrder(BiTree T) {
  if (!T) return;
  inOrder(T->lchild);
  printf("%c ", T->data);
  inOrder(T->rchild);
}

// 后序遍历
void postOrder(BiTree T) {
  if (!T) return;
  postOrder(T->lchild);
  postOrder(T->rchild);
  printf("%c ", T->data);
}

int main(void) {
  BiTree T;

  createTree(&T);

  printf("前序遍历：");
  preOrder(T);
  printf("\n");

  printf("中序遍历：");
  inOrder(T);
  printf("\n");

  printf("后序遍历：");
  postOrder(T);
  printf("\n");
  return 0;
}
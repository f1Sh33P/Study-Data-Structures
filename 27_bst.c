// binary search tree (BST) -- 二叉排序树
// 不能有重复值
// 查找速度快，插入删除灵活
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct treeNode {
  ElemType data;
  struct treeNode *lchild, *rchild;
} TreeNode, *BiTree;

int tree_arr[] = {70, 55, 49, 30, -1, 39, -1, -1, 53, -1, -1, -1, 80, 75, -1, -1, 98, 95, -1, -1, -1};
int idx = 0;

/*
                  70
            ┌──────┴──────┐
           55            80
        ┌───┘         ┌───┴───┐
       49            75      98
     ┌──┴──┐               ┌──┘
    30    53              95
     └─┐
      39
*/

void createTree(BiTree *T) {
  ElemType num = tree_arr[idx++];

  if (num == -1) *T = NULL;
  else {
    *T = (BiTree)malloc(sizeof(TreeNode));
    (*T)->data = num;
    createTree(&(*T)->lchild);
    createTree(&(*T)->rchild);
  }
}

void preOrder(BiTree T) {
  if (!T) return;

  printf("%d ", T->data);
  preOrder(T->lchild);
  preOrder(T->rchild);
}

int search(BiTree T, int value, BiTree parent, BiTree *pos) {
  if (!T) {
    *pos = parent;
    return 0;
  }

  if (value == T->data) {
    *pos = T;
    return 1;
  }

  if (value < T->data)
    return search(T->lchild, value, T, pos);
  else
    return search(T->rchild, value, T, pos);
}

int insert(BiTree *T, int value) {
  BiTree parent, pos;
  BiTree curr;

  int status = search(*T, value, NULL, &pos);

  // 如果 value 不在树中
  if (!status) {
    curr = (BiTree)malloc(sizeof(TreeNode));
    curr->data   = value;
    curr->lchild = NULL;
    curr->rchild = NULL;

    if (!pos)                   *T = curr;
    else if (value < pos->data) pos->lchild = curr;
    else                        pos->rchild = curr;

    return 1;
  } else
    return 0; // value 在树中
}

int deleteNode(BiTree *T, int value) {
  if (!*T) return 0;

  if (value < (*T)->data)
    return deleteNode(&(*T)->lchild, value);
  else if (value > (*T)->data)
    return deleteNode(&(*T)->rchild, value);
  else {
    BiTree temp = *T;

    if (!(*T)->rchild) {
      // 叶子结点或只有左子树
      *T = (*T)->lchild;
      free(temp);
    } else if (!(*T)->lchild) {
      // 只有右子树
      *T = (*T)->rchild;
      free(temp);
    } else {
      // 左右子树都有，用左子树中最大的结点替换
      BiTree record = (*T)->lchild;

      while (record->rchild) {
        record = record->rchild;
      }

      (*T)->data = record->data;

      return deleteNode(&(*T)->lchild, record->data);
    }
    return 1;
  }
}

int main(void) {
  BiTree T;
  BiTree pos;

  createTree(&T);
  preOrder(T);
  printf("\n");

  search(T, 53, NULL, &pos);
  printf("%d\n", pos->data);

  insert(&T, 99);
  preOrder(T);
  printf("\n");

  deleteNode(&T, 49);
  preOrder(T);
  printf("\n");

  return 0;
}
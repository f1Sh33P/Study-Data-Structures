// 单链表
// 从 0 开始的 for 循环，执行次数为小于号后的数字，如 for (int i = 0; i < n; i++) 执行 n 次
// if (p != NULL) 相当于 if (p)
// if (p == NULL) 相当于 if (!p)
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node {
  ElemType data;
  struct node *next; // 递归的感觉
} Node;

// initialize
Node *initList() {
  Node *head = (Node *)malloc(sizeof(Node));
  head->data = 0; // 头结点不存数据
  head->next = NULL;
  return head;
}

// 头插法
int insertHead(Node *L, ElemType e) {
  Node *p = (Node *)malloc(sizeof(Node));
  p->data = e;
  p->next = L->next;
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
  q->next = p->next;
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
  p->next = q->next; // 让 pos 的前驱指向 pos 的后继，跳过 pos
  free(q);           // 释放 pos
  return 1;
}

// 获取链表长度（不包括头结点）
int listLength(Node *L) {
  int len = 0;
  for (Node *p = L->next; p; p = p->next) len++;
  return len;
}

// 释放链表（不包括头结点）
void freeList(Node *L) {
  for (Node *p = L->next, *q; p; p = q) {
    q = p->next;
    free(p);
  }
  L->next = NULL;
}

// 单链表应用 #1：查找倒数第 k 个结点 -- 双指针
int findNode(Node *L, int k) {
  Node *fast = L->next;
  Node *slow = L->next;

  // 快指针先走 k 步
  for (int i = 0; i < k; i++) {
    if (!fast) return 0;
    fast = fast->next;
  }

  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }

  printf("倒数第 %d 个结点为 %d\n", k, slow->data);
  return 1;
}

// #2：删除绝对值相同的结点 -- 以空间换时间
void removeNode(Node *L, int n) {
  Node *p = L;
  int *q = (int *)malloc(sizeof(int) * (n + 1)); // 数组
  int index;                                     // 数组下标

  for (int i = 0; i < n + 1; i++)
    *(q + i) = 0;

  while (p->next) {
    index = abs(p->next->data);

    // 保留第一次遇到的结点，再遇到则删除
    if (*(q + index) == 0) {
      *(q + index) = 1;
      p = p->next;
    } else {
      Node *temp = p->next;
      p->next = temp->next;
      free(temp);
    }
  }
  free(q);
}

// #3：反转链表 -- 三指针
void reverseList(Node *head) {
  Node *first = NULL;
  Node *second = head->next; // second 存第一个结点
  Node *third;

  while (second) {
    third = second->next; // third 指向 second 的后继
    second->next = first; // 反转
    first = second;       // 移动
    second = third;       // 移动
  }

  head->next = first;
}

// #4：删除中间结点 -- 双指针
int delMiddleNode(Node *head) {
  Node *fast = head->next;
  Node *slow = head;

  // 快指针走两步，慢指针走一步
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  // 此时 slow 指向中间结点的前驱
  Node *q = slow->next;
  if (q) {
    slow->next = q->next;
    free(q);
  }
  return 1;
}

// #5：判断是否有环，并找到环的入口 -- 双指针
Node *circle(Node *head) {
  Node *fast = head;
  Node *slow = head;

  // 快指针走两步，慢指针走一步，若快慢指针相遇，说明有环
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;

    /* (a) 先统计环中结点数量，然后从头结点出发，快指针先走 count 步，再让快慢指针同步前进，相遇处即为环的入口
    if (fast == slow) {
      int count = 1;
      for (Node *p = fast; p->next != slow; p = p->next) count++;

      fast = slow = head;
      for (int i = 0; i < count; i++) fast = fast->next;

      while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
      }
      return slow;
    }
    */

    // (b) 从相遇处和头结点出发两个速度相同的指针，再次相遇处即为环的入口
    if (fast == slow) {
      slow = head;
      while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
      }
      return slow;
    }
  }
  return NULL;
}

int main(void) {
  Node *list = initList();

  insertHead(list, 10);
  insertHead(list, 20);
  insertHead(list, 30);

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

  printf("Length = %d\n", listLength(list));

  findNode(list, 2);

  freeList(list);
  printf("Length = %d\n", listLength(list));
  return 0;
}
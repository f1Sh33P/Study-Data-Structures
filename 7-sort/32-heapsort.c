// 堆排序
#include <stdio.h>

void swap(int *data, int m, int n) {
  int temp = data[m];
  data[m] = data[n];
  data[n] = temp;
}

void adjust(int *data, int root, int len) {
  int child = root * 2;
  int temp = data[root];

  // 找左右子树中最大的结点
  while (child <= len) {
    // 先找左右孩子中最大的结点
    if (child < len && data[child] < data[child + 1])
      child++;
    if (temp > data[child])
      break;

    data[child / 2] = data[child];
    child *= 2;
  }

  data[child / 2] = temp;
}

// 以升序为例
void heapsort(int *data, int len) {
  // #1 建堆：从最后一个非叶子结点开始向上调整
  for (int i = len / 2; i > 0; i--)
    adjust(data, i, len);

  // #2 排序：将堆顶最大值依次交换到数组末尾，并调整剩余部分为大根堆
  for (int i = len; i > 1; i--) {
    swap(data, 1, i);
    adjust(data, 1, i - 1);
  }
}

int main(void) {
  int data[] = {-1, 47, 35, 60, 95, 77, 15, 28}; // data[0] 未使用
  int len = sizeof(data) / sizeof(data[0]);

  heapsort(data, len - 1);

  for (int i = 1; i < len; i++)
    printf("%d ", data[i]);

  return 0;
}
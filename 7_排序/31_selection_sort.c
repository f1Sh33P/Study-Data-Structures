// 简单选择排序
// #1 时间复杂度：O(n²)
// #2 空间复杂度：O(1)
// #3 不稳定
// #4 适用场景：小规模数据排序
#include <stdio.h>

void swap(int *data, int m, int n) {
  int temp = data[m];
  data[m] = data[n];
  data[n] = temp;
}

// 以升序为例
void selectionSort(int *data, int len) {
  for (int i = 0; i < len; i++) {
    int min = i;

    for (int j = i; j < len; j++)
      if (data[min] > data[j]) min = j;

    if (i != min) swap(data, i, min);
  }
}

int main(void) {
  int data[] = {47, 35, 60, 95, 77, 15, 28};
  int len = sizeof(data) / sizeof(data[0]);

  selectionSort(data, len);

  for (int i = 0; i < len; i++)
    printf("%d ", data[i]);

  return 0;
}
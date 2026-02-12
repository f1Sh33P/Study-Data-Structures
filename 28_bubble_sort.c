// 冒泡排序
// #1 时间复杂度：平均 O(n²)，最好 O(n)，最坏 O(n²)
// #2 空间复杂度：O(1)
// #3 稳定
// #4 适用场景：数据量较小、对稳定性有要求
#include <stdio.h>

void swap(int *data, int m, int n) {
  int temp = data[m];
  data[m] = data[n];
  data[n] = temp;
}

// 以升序为例，相邻元素两两比较，一次循环排好一个数，将大数“沉底”，len 个数共需 len - 1 次循环
void bubbleSort(int *data, int len) {
  for (int i = 0; i < len - 1; i++)
    for (int j = 0; j < len - i - 1; j++)
      if (data[j] > data[j + 1])
        swap(data, j, j + 1);
}

int main(void) {
  int data[] = {47, 35, 60, 95, 77, 15, 28};
  int len = sizeof(data) / sizeof(data[0]);

  bubbleSort(data, len);

  for (int i = 0; i < len; i++)
    printf("%d ", data[i]);

  return 0;
}
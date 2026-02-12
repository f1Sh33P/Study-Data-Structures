// 插入排序 -- 将数组分为“已排序”和“未排序”两部分，依次将未排序的元素插入到已排序序列的正确位置
// #1 时间复杂度：平均 O(n²)，最好 O(n)，最坏 O(n²)
// #2 空间复杂度：O(1)
// #3 稳定
// #4 适用场景：数据规模小或者部分有序，常用于教学或小规模数据处理
#include <stdio.h>

// 以升序为例
void insertionSort(int *data, int len) {
  // i 之前为“已排序”的部分，之后为“未排序”的部分
  for (int i = 1; i < len; i++) {
    int temp = data[i];
    int j = i - 1;

    while (j >= 0 && data[j] > temp) {
      data[j + 1] = data[j];
      j--;
    }

    data[j + 1] = temp; // 前面 j 自减了，此处应加回来
  }
}

int main(void) {
  int data[] = {47, 35, 60, 95, 77, 15, 28};
  int len = sizeof(data) / sizeof(data[0]);

  insertionSort(data, len);

  for (int i = 0; i < len; i++)
    printf("%d ", data[i]);

  return 0;
}
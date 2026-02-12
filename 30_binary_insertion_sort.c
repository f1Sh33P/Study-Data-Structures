// 折半插入排序
// #1 时间复杂度：平均 O(n²)，最好 O(n log n)，最坏 O(n²)
// #2 空间复杂度：O(1)
// #3 稳定
// #4 适用场景：数据基本有序或对稳定性有要求
#include <stdio.h>

// 以升序为例
void binaryInsertionSort(int *data, int len) {
  for (int i = 1; i < len; i++) {
    int temp = data[i];
    int low = 0;
    int high = i - 1;
    int mid;

    while (low <= high) {
      mid = (low + high) / 2;

      if (data[mid] > temp) high = mid - 1;
      else                  low = mid + 1;
    }

    int j = i - 1;
    while (j >= low) {
      data[j + 1] = data[j];
      j--;
    }

    data[low] = temp;
  }
}

int main(void) {
  int data[] = {47, 35, 60, 95, 77, 15, 28};
  int len = sizeof(data) / sizeof(data[0]);

  binaryInsertionSort(data, len);

  for (int i = 0; i < len; i++)
    printf("%d ", data[i]);

  return 0;
}
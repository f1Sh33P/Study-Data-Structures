// 二分查找
// 需要数据先排好序
#include <stdio.h>

int binarySearch(int *data, int len, int value) {
  int low = 0;
  int high = len - 1;
  int mid;

  while (low <= high) {
    mid = (low + high) / 2;
    if (value > data[mid])      low = mid + 1;
    else if (value < data[mid]) high = mid - 1;
    else                        return mid;
  }
  return -1;
}

int main(void) {
  int arr[] = {2, 13, 22, 38, 46, 58, 66, 77, 85, 98};
  int len = sizeof(arr) / sizeof(arr[0]);
  int pos = binarySearch(arr, len, 66);

  printf("%d\n", pos);
  return 0;
}
// 顺序查找
#include <stdio.h>

int search(int *data, int len, int value) {
  for (int i = 0; i < len; i++)
    if (data[i] == value) return i;
  return -1;
}

int main(void) {
  int arr[] = {15, 54, 76, 6, 9, 45, 12}; // 查找表
  int len = sizeof(arr) / sizeof(arr[0]); // 数组长度
  int pos = search(arr, len, 45);

  printf("%d\n", pos);
  return 0;
}
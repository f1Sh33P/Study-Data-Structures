// 枚举
#include <stdio.h>

// enumeration
typedef enum {
  mon, // 0
  tue, // 1
  wed, // 2
  thu, // 3
  fri, // 4
  sat, // 5
  sun  // 6
} Weekday;

int main(void) {
  Weekday a = mon;
  Weekday b = tue;

  printf("%d\n", a);
  printf("%d\n", b);
  return 0;
}
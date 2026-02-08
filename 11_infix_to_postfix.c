// 中缀表达式转后缀表达式
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef enum {
  LEFT_PARE, RIGHT_PARE,
  ADD, SUB, MUL, DIV, MOD,
  EOS, NUM
} ContentType;

typedef struct {
  ContentType *data;
  int top;
} Stack;

char expr[] = "x/(i-j)*y";

Stack *initStack() {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->data = (ContentType *)malloc(sizeof(ContentType) * MAXSIZE);
  s->top = -1;
  return s;
}

int push(Stack *s, ContentType e) {
  if (s->top == MAXSIZE - 1) {
    printf("Full\n");
    return 0;
  }
  s->data[++s->top] = e;
  return 1;
}

int pop(Stack *s, ContentType *e) {
  if (s->top == -1) {
    printf("Empty\n");
    return 0;
  }
  *e = s->data[s->top--];
  return 1;
}

ContentType getToken(char *symbol, int *index) {
  *symbol = expr[(*index)++];

  switch (*symbol) {
    case '(':  return LEFT_PARE;
    case ')':  return RIGHT_PARE;
    case '+':  return ADD;
    case '-':  return SUB;
    case '*':  return MUL;
    case '/':  return DIV;
    case '%':  return MOD;
    case '\0': return EOS;
    default:   return NUM;
  }
}

int printToken(ContentType token) {
  switch (token) {
    case ADD: printf("+");  break;
    case SUB: printf("-");  break;
    case MUL: printf("*");  break;
    case DIV: printf("/");  break;
    case MOD: printf("%%"); break;
    default:  return 0;
  }
  return 1;
}

void postfix(Stack *s) {
  int in_stack[] = {0, 19, 12, 12, 13, 13, 13, 0};   // 栈内优先级，分别对应 LEFT_PARE, RIGHT_PARE, ADD, SUB, MUL, DIV, MOD, EOS
  int out_stack[] = {20, 19, 12, 12, 13, 13, 13, 0}; // 栈外优先级，分别对应 LEFT_PARE, RIGHT_PARE, ADD, SUB, MUL, DIV, MOD, EOS
  int index = 0;
  char symbol;

  ContentType token;
  ContentType e;

  push(s, EOS);

  while ((token = getToken(&symbol, &index)) != EOS) {
    // #1 遇到 NUM 则直接输出
    if (token == NUM) printf("%c", symbol);

    // #2 遇到 RIGHT_PARE，就输出 LEFT_PARE 后的全部运算符
    else if (token == RIGHT_PARE) {
      while (s->data[s->top] != LEFT_PARE) {
        pop(s, &e);
        printToken(e);
      }
      pop(s, &e); // 丢弃 LEFT_PARE
    }

    // #3 若 token 的优先级小于或等于栈顶元素的优先级，则依次输出栈中元素，否则将 token 进栈
    else {
      while (out_stack[token] <= in_stack[s->data[s->top]]) {
        pop(s, &e);
        printToken(e);
      }
      push(s, token);
    }
  }

  // 将剩余元素依次出栈
  while (s->data[s->top] != EOS) {
    pop(s, &e);
    printToken(e);
  }
  printf("\n");
}

int main(void) {
  Stack *s = initStack();
  printf("%s\n", expr);
  postfix(s);
  return 0;
}
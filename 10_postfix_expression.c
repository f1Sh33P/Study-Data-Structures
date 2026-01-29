// 后缀表达式
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

typedef struct {
  ElemType *data;
  int top;
} Stack;

typedef enum {
  LEFT_PARE, RIGHT_PARE, // parenthesis
  ADD, SUB, MUL, DIV, MOD,
  EOS, NUM
} ContentType;

char expr[] = "82/2+56*-";

Stack *initStack() {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->data = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
  s->top = -1;
  return s;
}

int push(Stack *s, ElemType e) {
  if (s->top == MAXSIZE - 1) {
    printf("Full\n");
    return 0;
  }
  s->data[++s->top] = e;
  return 1;
}

int pop(Stack *s, ElemType *e) {
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

int eval(Stack *s) {
  char symbol;
  int op1, op2;
  int index = 0;

  ContentType token = getToken(&symbol, &index);
  ElemType result;

  while (token != EOS) {
    // #1
    if (token == NUM)
      push(s, symbol - '0');

    // #2
    else {
      pop(s, &op2);
      pop(s, &op1);

      switch (token) {
        case ADD: push(s, op1 + op2); break;
        case SUB: push(s, op1 - op2); break;
        case MUL: push(s, op1 * op2); break;
        case DIV: push(s, op1 / op2); break;
        case MOD: push(s, op1 % op2); break;
        default:  break;
      }
    }

    // #3
    token = getToken(&symbol, &index);
  }

  pop(s, &result);
  printf("%d\n", result);
  return 1;
}

int main(void) {
  Stack *s = initStack();
  eval(s);
  return 0;
}
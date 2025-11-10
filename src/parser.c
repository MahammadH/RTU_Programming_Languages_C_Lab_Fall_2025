#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char s[200];
int p;
char c;

void nxt() { c = s[p++]; }

int expr();  // ileri bildirim

int num() {
  int x = 0;
  if (!isdigit(c)) {
    printf("error\n");
    exit(1);
  }
  while (isdigit(c)) {
    x = x * 10 + (c - '0');
    nxt();
  }
  return x;
}

int factor() {
  if (c == '(') {
    nxt();
    int x = expr();
    if (c == ')')
      nxt();
    else {
      printf("paren error\n");
      exit(1);
    }
    return x;
  } else {
    return num();
  }
}

int term() {
  int x = factor();
  while (c == '*' || c == '/') {
    char op = c;
    nxt();
    int y = factor();
    if (op == '*')
      x = x * y;
    else {
      if (y == 0) {
        printf("zero div\n");
        exit(1);
      }
      x = x / y;
    }
  }
  return x;
}

int expr() {
  int x = term();
  while (c == '+' || c == '-') {
    char op = c;
    nxt();
    int y = term();
    if (op == '+')
      x = x + y;
    else
      x = x - y;
  }
  return x;
}

int main() {
  printf("expr: ");
  if (!fgets(s, sizeof(s), stdin)) return 1;
  p = 0;
  nxt();
  int r = expr();
  printf("= %d\n", r);
  return 0;
}

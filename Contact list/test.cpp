#include <iostream>
#include "stack.h"
using namespace std;

struct Stack {
  void *my_stack[100];
  int top;
};

bool is_empty( Stack s ) {
  s->my_stack[top] == NULL ? true : false;
}

void push( Stack s ) {
  s->my_stack[s->top] = s;
  s->top++;
}

void *pop( Stack s ) {
  delete s->my_stack[s->top];
  s->top--;
}

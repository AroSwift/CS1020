#include <iostream>
using namespace std;

struct Stack {
  void *my_stack[100];
  int top;
};

void init_stack(Stack *S) {
  s->top = -1;
}

bool is_empty( Stack *s ) {
  s->my_stack[s->top] == NULL ? true : false;
}

void push( Stack *s, void *data ) {
  s->top++;
  s->my_stack[s->top] = data;
}

void *pop( Stack *s ) {
  void *return = s->my_stack[top];
  s->my_stack.top--;
}

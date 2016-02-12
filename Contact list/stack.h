#include <iostream>
#include "stack.h"

using namespace std;

struct Stack {
  void *myStack[100];
  int  top;
};

void initStack(Stack *s);
void push(Stack s, void *data);
void *pop(Stack s);
bool isEmpty(Stack s);

void initStack(Stack *s) {
  s->top = -1;
}

void push(Stack *s, void *data) {
   s->top++;
   s->myStack[s->top] = data; // should make a copy here...
}

void *pop(Stack *s) {
  void *retVal = s->myStack[s->top];
  s->top--;
  return(retVal);
}

bool isEmpty(Stack *s) {
  return(s->top != -1);
}
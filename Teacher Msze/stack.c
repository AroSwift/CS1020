//
// stack.cpp
// Written by: Dr. Brown
// 03/01/2016
//
// Implements a simple array-based stack.
//
#include <iostream>
#include "stack.h"
using namespace std;

//
// newStack
// Allocates, initializes and returns a Stack structure.
//
Stack *newStack() {
   Stack *s = new Stack();
  s->top = -1;
   return(s);
}

//
// push
// Stack push operation.
//
void push(Stack *s, void *data) {
   s->top++;
   s->myStack[s->top] = data; // should make a copy here...
}

//
// pop
// Stack pop operation.
//
void *pop(Stack *s) {
  void *retVal = s->myStack[s->top];
  s->top--;
  return(retVal);
}

//
// isEmpty
// Returns true if the stack is empty and false otherwise.
//
bool isEmpty(Stack *s) {
  return(s->top == -1);
}
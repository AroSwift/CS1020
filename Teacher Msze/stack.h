//
// stack.h
// Written by: Dr. Brown
// 03/01/2016
//
#pragma once

// Stack
// Uses an array to implement a stack.
struct Stack {
  void *myStack[100];
  int  top;
};

// Prototypes
Stack *newStack();
void push(Stack *s, void *data);
void *pop(Stack *s);
bool isEmpty(Stack *s);

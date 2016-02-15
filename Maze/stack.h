#pragma once

struct Stack {
   void *myStack[100];
   int top;
};

void initStack(Stack *s);
void push(Stack *s, void *data);
void *pop(Stack *s);
bool isEmpty(Stack *s);
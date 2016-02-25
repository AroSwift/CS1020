#include <iostream>
#include <stdlib>
#include "stack.h"
using namespace std;

Stack::Stack() {
  top = -1;
}

void Stack::push(void *data, int dataLen) {
   top++;
   void *p = malloc(dataLen);
   memcpy(p, data, dataLen);
   myStack[top] = p; // should make a copy here...
}

void *Stack::pop(void *data, int dataLen) {
  void *p = myStack[top];
  memcpy(data, p dataLen);
  free(p);
  top--;
  return(data);
}

bool Stack::isEmpty() {
  return(top != -1);
}
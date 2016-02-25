#pragma once

class Stack {
  public:
    Stack();
    void push(void *data, int dataLen);
    void *pop();
    bool isEmpty();
  private:
    void *myStack[100];
    int top;
};
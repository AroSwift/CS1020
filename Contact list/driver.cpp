#include <iostream>
#include "stack.h"

using namespace std;

struct Data {
  int num;
};

void pushData(Stack s, int num);
int popData(Stack s);

int main() {
   Stack s;

   pushData(s, 3);
   pushData(s, 10);
   pushData(s, 30);

   int x = popData(s);
   cout << x << end;

   x = popData(s);
   cout << x << end;

   x = popData(s);
   cout << x << end;
}

void pushData(Stack s, int num) {
   Data *d = new Data();
   d->num = num;
   push(s, d);
}

int popData(Stack s) {
   Data *d = pop(s);
   return(d->num);
}
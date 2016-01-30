#include <iostream>
#include <stdlib.h>
using namespace std;

struct Names {
  string name;
  void *next;
};

void traverse( Names *first );

int main() {
  Names *n = (Names *)malloc(sizeof(Names));
  Names *first = n;

  n->name = "David";
  n->next = (Names *)malloc(sizeof(Names));
  n = n->next;

  n->name = "Karen";
  n->next = (Names *)malloc(sizeof(Names));
  n = n->next;

  n->name = "Pam";
  n->next = (void *)0;

  traverse( first );

  return 0;

}

void traverse( Names *first ) {

  while( first != (void *)0 ) {
    cout << first->name << endl;
    first = first->next;
  }

}
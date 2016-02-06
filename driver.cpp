#include <iostream>
#include “linked_list.h”
using namespace std;

int main() {
  Node *first = NULL;
  insert_first( &first, (Void *)“David” );
  insert_first( &first, (Void *)“Pam” );
  insert_first( &first, (Void *)“Karen” );
  Node *current = first;

  while( current != NULL ) {
  cout << (string)current->data << endl;
  current = getNext(current);
  }

}
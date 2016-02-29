//
// queue.cpp
// Written by: Aaron Barlow
// 02/28/2016
//
// General queue code library that allow the intialization, insertion,
// removal of last element in queue, and removal of all elements in queue.
//

#include <iostream>
#include <cstdlib>
#include "queue.h"
using namespace std;

// FIFO scheme
Queue *newQueue() {
  Queue *q = new Queue();
  q->last = q->first = NULL;
  return q;
}


// Insert into the back node
void insert(Queue *q, void *data) {
    Node *new_node = new Node();
    new_node->data = data;
    new_node->next = new_node->prev = NULL;

    if(q->last != NULL) {
      new_node->prev = q->last;
      q->last->next = new_node;
    } else {
      q->first = new_node;
    }

    q->last = new_node;
}


// Remove from the front node
void *remove(Queue *q) {
  if(q->first == NULL) return NULL;
  void *removed_node = q->first;

  q->first = q->first->next;
  q->first->prev = NULL;
  return removed_node;
}


void removeAll(Queue *q) {
  while(q->first != NULL) remove(q);
}

struct Random {
  int num;
};


int main() {
  Queue *q = newQueue();

  Random *r = new Random();
  r->num = 5;
  insert( q, r );

  Random *r2 = new Random();
  r2->num = 7;
  insert( q, r2 );

  Random *out = (Random*)remove( q );
  cout << out->num << endl;

}



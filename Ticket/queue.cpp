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

  cout << "here are we?" << endl;

  return q;
}


// Insert into the back node
void insert(Queue *q, void *data) {
    Node *new_node = new Node();
    new_node->data = data;
    new_node->next = new_node->prev = NULL;

    if(q->first != NULL) {
      new_node->next = q->first;
      q->first->next = new_node;
    }

   cout << "insert we do?" << endl;

    q->first = new_node;
    // if(q->last == NULL) q->last = new_node;
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
  Random *r = new Random();
  r->num = 5;

  Queue *q = newQueue();
  insert( q, r );

  Random *r2 = new Random();
  r2->num = 7;

  insert( q, r2 );
  Random *out = (Random*)remove( q );
  cout << out->num << endl;

}



//
// queue.cpp
// Written by: Aaron Barlow
// 03/2/2016
//
// General queue code library that allow the intialization, insertion, and
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

  if(q->last == NULL) {
    q->first = new_node;
  } else {
    new_node->prev = q->last;
    q->last->next = new_node;
  }

  q->last = new_node;
}


// Remove from the front node
void *remove(Queue *q) {
  if(q->first == NULL) return NULL;
  void *removed_node = q->first->data;
  q->first->prev = NULL;

  if(q->first->next == NULL) {
    q->first = NULL;
    q->last = NULL;
  } else {
    q->first = q->first->next;
  }

  return removed_node;
}

bool queue_empty(Queue *q) {
  return q->last == NULL && q->first == NULL ? true : false;
}



// struct Wow {
//   int number;
// };

// int main() {
//   Queue *q = newQueue();

//   Wow *w = new Wow();
//   w->number = 5;
//   insert( q, (void*)w );

//   Wow *w2 = new Wow();
//   w2->number = 25;
//   insert( q, (void*)w2 );

//   Wow *w3 = new Wow();
//   w3->number = 100;
//   insert( q, (void*)w3 );

//   Wow *removed = (Wow*)remove(q);
//   cout << removed->number << endl;

//   Wow *removed2 = (Wow*)remove(q);
//   cout << removed2->number << endl;

//   Wow *w4 = new Wow();
//   w4->number = 111;
//   insert( q, (void*)w4 );

//   Wow *w5 = new Wow();
//   w5->number = 122;
//   insert( q, (void*)w5 );

//   Wow *removed3 = (Wow*)remove(q);
//   cout << removed3->number << endl;

//   Wow *w6 = new Wow();
//   w6->number = 125;
//   insert( q, (void*)w6 );

//   Wow *removed4 = (Wow*)remove(q);
//   cout << removed4->number << endl;

//   Wow *removed5 = (Wow*)remove(q);
//   cout << removed5->number << endl;

//   Wow *removed6 = (Wow*)remove(q);
//   cout << removed6->number << endl;

// }

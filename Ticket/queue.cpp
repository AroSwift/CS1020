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
  void *removed_node = q->first;
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
  return q->last == NULL || q->first == NULL ? true : false;
}

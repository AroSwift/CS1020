#include <iostream>
#include <cstddef>
#include "linked_list.h"


void insertFirst(Node **first, void *data) {
   Node *p = new Node();
   p->data = data;
   p->next = NULL;
   if (*first != NULL)
      p->next = *first;
   *first = p;
}

void insertLast(Node **first, void *data) {
   // allocate the node
   Node *p = new Node();
   // initialize the node fields
   p->data = data;
   p->next = NULL;

   // if empty list
   if (*first == NULL)
      *first = p;
   else { // not empty list
      Node *last = findLast(*first);
      last->next = p;
   }
}

Node *findLast(Node *first) {
   if (first == NULL)
   return(NULL);
   // traverse list until NULL
   Node *node = first;
   while(node->next != NULL)
      node = node->next;
   return(node);
}

void get_next(Node *current_node) {
  if( current_node != NULL ) {
    return( current_node->next );
  }
}

void remove(Node *nodeToRemove, Node **first) {
  if (*first == NULL)
    return;
  if (*first == nodeToRemove) {
    *first = nodeToRemove->next;
    delete nodeToRemove;
  }
  else {
    Node *before = *first;
    Node *current = *first;
    while(current != nodeToRemove) {
      if (current == NULL)
        break;
      before = current;
      current = current->next;
    }
    if (current == nodeToRemove) {
      before->next = current->next;
      delete current;
    }
  }
}

void removeFirst(Node **first) {
  remove(*first,first);
}

void removeLast(Node **first) {
  remove(findLast(*first), first);
}

Node *search(void *data) {
}

Node *get() {
}

void set() {
}
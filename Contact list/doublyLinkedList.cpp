#include <iostream>
#include <cstddef>
#include "linkedList.h"

void insertFirst(Node **first, Node **last, void *data) {
   Node *p = new Node();
   p->data = data;
   p->next = p->prev = NULL;
   if (*first != NULL) {
      p->next = *first;
    (*first)->prev = p;
   }
   *first = p;
   if (*last == NULL)
      *last = p;
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

Node *getNext(Node *currentNode) {
  if (currentNode != NULL)
    return(currentNode->next);
    return(NULL);
}

Node *getPrev(Node *currentNode) {
  if (currentNode != NULL)
    return(currentNode->prev);
    return(NULL);
}

void remove(Node *nodeToRemove, Node **first, Node **last) {
  //check for empty list
  if (*first == NULL)
    return;

  // Removing first node
  if (*first == nodeToRemove) {
    (*first) = (*first)->next;
    (*first)->prev = NULL;
  }
  // Removing last node
  if (*last == nodeToRemove) {
    (*last) = (*last)->prev;
    (*last)->next = NULL;
  }
  // At least 3 nodes
  if ((*first != nodeToRemove) && (*last != nodeToRemove)) {
    nodeToRemove->prev->next = nodeToRemove->next;
    nodeToRemove->next->prev = nodeToRemove->prev;
  }
  delete nodeToRemove;
}

void removeFirst(Node **first) {
  remove(*first,first);
}

void removeLast(Node **first) {
  remove(findLast(*first), first);
}

void set(Node *nodeToSet, void *data) {
  if (nodeToSet != NULL) {
                if (data != nodeToSet->data) {
                   void *tempData = nodeToSet->data;
       nodeToSet->data = data;
                   delete tempData;
        }
}
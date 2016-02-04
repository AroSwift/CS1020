#include <iostream>
#include <cstddef>
#include "linked_list.h"


void insertFirst(Person **first, string name) {
   Person *p = new Person();
   p->name = name;
   p->next = NULL;
   if (*first != NULL)
      p->next = *first;
   *first = p;
}

void insertLast(Person **first, string name) {
   // allocate the node
   Person *p = new Person();
   // initialize the node fields
   p->name = name;
   p->next = NULL;

   // if empty list
   if (*first == NULL)
      *first = p;
   else { // not empty list
      Person *last = findLast(*first);
      last->next = p;
   }
}

Person *findLast(Person *first) {
   if (first == NULL)
   return(NULL);
   // traverse list until NULL
   Person *node = first;
   while(node->next != NULL)
      node = node->next;
   return(node);
}

void traverse(Person *first) {
   while(first != NULL) {
      cout << first->name << endl;
      first = first->next;
   }
}

void remove(Person *nodeToRemove, Person **first) {
  if (*first == NULL)
    return;
  if (*first == nodeToRemove) {
    *first = nodeToRemove->next;
    delete nodeToRemove;
  }
  else {
    Person *before = *first;
    Person *current = *first;
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

void removeFirst(Person **first) {
  remove(*first,first);
}

void removeLast(Person **first) {
  remove(findLast(*first), first);
}

Person *search(string name) {
}

Person *get() {
}

void set() {
}
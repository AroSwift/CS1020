#include <iostream>
#include <cstddef>

using namespace std;

struct Person {
 string name;
 Person *next;
};

void insertFirst(Person **first, string name);
void insertLast(Person **first, string name);
Person *findLast(Person *first);
void traverse(Person *first);

int main() {
 string names[] = {"David", "Pam", "Karen"};
 Person *first = NULL;

 for(int i = 0; i < 3; i++) {
 insertLast(&first, names[i]);
 }
 traverse(first);
}

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
  } else {
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


void remove_first( Person **first ) {
  remove( *first, first );
}

void remove_last( Person **first ) {
  // Person *last = findLast(*first);
  // remove(*last);
  remove(findLast(*first,));
}

void set( Person *node, string name ) {
  Person *p = new Person;
  p->name = name;
}
#pragma once
#include <iostream>
using namespace std;

struct Person {
 string name;
 Person *next;
};

void insertFirst(Person **first, string name);
void insertLast(Person **first, string name);
Person *findLast(Person *first);
void traverse(Person *first);
void remove(Person *nodeToRemove, Person **first);
void removeFirst(Person **first);
void removeLast(Person **first);


//  ONLY PROTYPES, STRUCTURES, AND CONSTANTS
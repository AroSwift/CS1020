#pragma once
#include <iostream>
using namespace std;

struct Node {
 void data;
 Node *next;
};

void insertFirst(Node **first, void *data);
void insertLast(Node **first, void *data);
Node *findLast(Node *first);
void traverse(Node *first);
void remove(Node *nodeToRemove, Node **first);
void removeFirst(Node **first);
void removeLast(Node **first, void *data);


//  ONLY PROTYPES, STRUCTURES, AND CONSTANTS
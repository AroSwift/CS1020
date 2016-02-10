//
// Doubly-linked Lists
//
#pragma once
#include <iostream>
using namespace std;

struct Node {
   void *data;
   Node *next, *prev;
};

void insertFirst(Node **first, Node **last, void *data);
void insertLast(Node **first, Node **last, void *data);
Node *getNext(Node *currentNode);
Node *getPrev(Node *currentNode);
void remove(Node *nodeToRemove, Node **first, Node **last);
void removeFirst(Node **first, Node **last);
void removeLast(Node **first, Node **last);
void set(Node *nodeToSet, void *data);
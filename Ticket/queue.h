#pragma once
//
// queue.h
// Written by: Aaron Barlow
// 03/2/2016
//
// Header file for queue structures and prototypes.
//

struct Node {
  Node *next, *prev;
  void *data;
};

struct Queue {
  Node *first, *last;
};


Queue *newQueue();
void insert(Queue *q, void *data);
void *remove(Queue *q);
bool queue_empty( Queue *q );
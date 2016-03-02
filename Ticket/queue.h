#pragma once
//
// queue.h
// Written by: Aaron Barlow
// 03/2/2016
//
// Header file for queue code.
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
bool is_empty( Queue *q );
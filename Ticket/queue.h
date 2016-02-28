#pragma once
//
// queue.h
// Written by: Aaron Barlow
// 02/28/2016
//
// Header file for queue code.
//

struct Node {
  Node *next;
  void *data;
};

struct Queue {
  Node *first, *last;
};


Queue *newQueue();
void insert(Queue *q, void *data);
void *remove(Queue *q);
// void removeAll(Queue *q);
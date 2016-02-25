#pragma once

struct Node {
  Node *next, *prev;
};

struct Queue {
  Node *front, *rear;
  void *data;
};


Queue *newQueue();
void insert(Queue *q, void *data);
void *remove(Queue *q);
void removeAll(Queue *q);
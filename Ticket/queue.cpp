//
// queue.cpp
// Written by: Aaron Barlow
// 02/28/2016
//
// General queue code library that allow the intialization, insertion,
// removal of last element in queue, and removal of all elements in queue.
//

#include <cstdlib>
#include <iostream>
#include "queue.h"
using namespace std;

// FIFO
Queue *newQueue() {
  Queue *q = new Queue();
  q->last = q->first = NULL;
  return q;
}


// void insertFirst(Node **first, void *data) {
//    Node *p = new Node();
//    p->data = data;
//    p->next = NULL;
//    if (*first != NULL)
//       p->next = *first;
//    *first = p;
// }


// Insert in the front
void insert(Queue *q, void *data) {
    Node *new_node = new Node();
    new_node->data = data;
    new_node->next = NULL;

  // First element in queue
  if( q->first == NULL && q->last == NULL ) {
    q->first = q->last = new_node;
  } else { // Elements already exist in queue
    new_node->next = q->first->next;
    q->first = new_node;
  }

}

// Remove from the back
void *remove(Queue *q) {
  void *old_last = q->first;
  Node *removed_element = new Node();
  removed_element = q->first;

  // while(q->last != q->first && ) {

  // }

  // Make front node the next node
  if( q->last != NULL ) {
    // Queue old_front = q->front;

    q->first = q->first->next;

    // Deallocate the old front queue
    // delete &old_front;
  }

  // Return pointer to null or to queue removed
  return removed_element;
}


// void removeAll(Queue *q) {

// }

struct Random {
  int num;
};


int main() {
  Random *r = new Random();
  r->num = 5;

  Queue *q = newQueue();
  insert( q, r );

  Random *r2 = new Random();
  r2->num = 7;

  insert( q, r2 );
  Random *out = (Random*)remove( q );
  cout << out->num << endl;

}



// #include<iostream>

// #include<cstdlib>

// using namespace std;

// struct node{

//     int info;

//     struct node *next;

// };

// class Queue{

//     private:

//         node *rear;

//         node *front;

//     public:

//         Queue();

//         void enqueue();

//         void dequeue();

//         void display();

// };

// Queue::Queue(){

//     rear = NULL;

//     front = NULL;

// }

// void Queue::enqueue(){

//     int data;

//     node *temp = new node;

//     cout<<"Enter the data to enqueue: ";

//     cin>>data;

//     temp->info = data;

//     temp->next = NULL;

//     if(front == NULL){

//         front = temp;

//     }else{

//         rear->next = temp;

//     }

//     rear = temp;

// }

// void Queue::dequeue(){

//     node *temp = new node;

//     if(front == NULL){

//         cout<<"\nQueue is Emtpty\n";

//     }else{

//         temp = front;

//         front = front->next;

//         cout<<"The data Dequeued is "<<temp->info;

//         delete temp;

//     }

// }

// void Queue::display(){

//     node *p = new node;

//     p = front;

//     if(front == NULL){

//         cout<<"\nNothing to Display\n";

//     }else{

//         while(p!=NULL){

//             cout<<endl<<p->info;

//             p = p->next;

//         }

//     }

// }

// int main(){

//     Queue queue;

//     int choice;

//     while(true){

//         cout<<"\n1.Enqueue\n2. Dequeue\n3. Display\n 4.Quit";

//         cout<<"\nEnter your choice: ";

//         cin>>choice;

//         switch(choice){

//             case 1:

//                 queue.enqueue();

//                 break;

//             case 2:

//                 queue.dequeue();

//                 break;

//             case 3:

//                 queue.display();

//                 break;

//             case 4:

//                 exit(0);

//                 break;

//             default:

//                 cout<<"\nInvalid Input. Try again! \n";

//                 break;

//         }

//     }

//     return 0;

// }
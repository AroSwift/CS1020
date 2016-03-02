//
// tickets.cpp
// Written by: Aaron Barlow
// 02/28/2016
//
// Simulated ticket processing system that will read in orders,
// process the orders, and then put the orders in a queue
// as the orders are recieved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
// #include <unistd.h>
#include <time.h>
#include "tickets.h"
using namespace std;

int main() {
  bool tickets_available = true;
  Order *order = new Order();
  order->queue = newQueue();

  order->confirmation_number = 1;
  order->starting_time = time(0);

  while(tickets_available) {
    order->get_orders();

    // If ticket time is equal to
    //  or less than current time, set that in queue

    order->process_orders();

  }

  delete order->queue;
  delete order;

  return 0;
}



void validate_file( ifstream& input ) {
  // Read in file
  input.open(FILE_NAME);

  // When file could not be found
  if( input.fail() ) {
    cout << "Input file " << FILE_NAME << " does not exist. \n";
    exit(1);

  // When file is empty
  } else if( input.peek() == EOF ) {
    cout << "Input file " << FILE_NAME << " is empty. \n";
    exit(1);
  }
}

void Order::get_orders() {
  ifstream input;

  // Open and validate file exists as well as contains content
  validate_file( input );

  // ticktime first-name last-name number-of-tickets
  while( !input.eof() ) {

    string seconds;
    getline( input, seconds );

    int tick_time = starting_time + atoi( seconds.c_str() );

    time_t current_time = time(0);
    if( tick_time >= current_time ) break;

    getline( input, first_name );
    getline( input, last_name );

    string tickets;
    getline( input, tickets );
    num_tickets = atoi( tickets.c_str() );

    // Order *o = new Order();
    // o = this;
    insert( this->queue, this);

  }

  input.close();

}

void Order::process_orders() {
  if( is_empty(queue) ) return;

  // Emulate processing the order
  current_time += SLEEP_TIME;


  while( num_tickets < NUM_TICKETS_AVAILABLE ) {
    Order *queued_order = (Order*)remove( queue );


    localtime();
    if( queued_order->tick_time > starting_time ) return;

    for( queued_order->num_tickets; queued_order->num_tickets < NUM_TICKETS_AVAILABLE )
      confirmation_number++;
    }
  }

}

void Order::print_orders() {
  // if( q->front == NULL || q->rear == NULL) do stuff

  // do {
  //   cout << order << endl;

  // } while(order->next != NULL);

  // convert time_t to localtime

  cout << " : " << endl;

}


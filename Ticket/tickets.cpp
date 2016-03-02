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
#include <unistd.h>
#include <time.h>
#include "tickets.h"
using namespace std;

int main() {
  bool tickets_available = true;
  Order *order = new Order();
  order->queue = newQueue();

  order->current_tick_time = 0;

  while(tickets_available) {
    order->get_orders();
    order->print_orders();

    sleep(SLEEP_TIME);
    // Then get tickets
    // Process tickets
    // If ticket time is equal to
    //  or less than current time, set that in queue

    if( order->num_tickets > NUM_TICKETS_AVAILABLE ) tickets_available = false;

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

    if( atoi(seconds.c_str()) > current_tick_time ) break;

    getline( input, first_name );
    getline( input, last_name );

    string tickets;
    getline( input, tickets );

    tick_time = atoi( seconds.c_str() );
    num_tickets = atoi( tickets.c_str() );

    insert( this->queue, this);

  }

  input.close();

}

void Order::print_orders() {
  // if( q->front == NULL || q->rear == NULL) do stuff

  // do {
  //   cout << order << endl;

  // } while(order->next != NULL);

  cout << " : " << endl;

}



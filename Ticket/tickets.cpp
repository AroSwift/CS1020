//
// tickets.cpp
// Written by: Aaron Barlow
// 03/2/2016
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
#include <time.h>
#include "tickets.h"
using namespace std;

int main() {

  cout << "MAIN?!!!" << endl;

  bool all_tickets_processed = false;
  Order *order = new Order();
  order->queue = newQueue();

  order->confirmation_number = 1;
  order->starting_time = time(0);

  cout << "Tickets available" << endl;

  while(!all_tickets_processed) {
    cout << "in while" << endl;
    order->get_orders();

    // If ticket time is equal to
    //  or less than current time, set that in queue

    order->process_orders();

    if( order->num_tickets == NUM_TICKETS_AVAILABLE && !queue_empty( order->queue ) ) {
      order->sold_out();
    }

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

  cout << "Get orders" << endl;

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

  cout << "Process orders "<< endl;

  if( queue_empty(queue) ) return;

  // Emulate processing the order
  tick_time += SLEEP_TIME;


  while( num_tickets < NUM_TICKETS_AVAILABLE ) {
    Order *queued_order = (Order*)queue->last;

    if( queued_order->tick_time > starting_time ) return;

    for( queued_order->num_tickets;
      queued_order->num_tickets < NUM_TICKETS_AVAILABLE; num_tickets++ ) {
      print_orders();
      confirmation_number++;
      remove( queue );
    }
  }

}

void Order::print_orders() {
  cout << "Print orders" << endl;

  Order *processed_order = (Order*)queue->last;


  // Timestamp - Order confirmation-number: last-name, first-name (number-of-tickets) tickets
  cout << confirmation_number << ": "
       << processed_order->last_name << " "
       << processed_order->first_name << "("
       << processed_order->num_tickets << ")"
       << processed_order->num_tickets << endl;


  cout << " : " << endl;
}

void Order::sold_out() {
  Order *unprocessed_order = (Order*)queue->last;

  cout << confirmation_number << ": "
       << unprocessed_order->last_name << " "
       << unprocessed_order->first_name << "("
       << unprocessed_order->num_tickets << ")"
       << unprocessed_order->num_tickets << endl;
}




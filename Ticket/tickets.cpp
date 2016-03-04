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
#include <unistd.h>
#include "tickets.h"
using namespace std;

int main() {
  Order *order = new Order();
  order->queue = newQueue();

  // Get the file
  ifstream input;
  get_file( input );

  order->confirmation_number = 1;
  order->starting_time = time(0);
  order->current_time = time(0);
  order->tick_time = order->current_time;

  while( order->num_tickets_used != NUM_TICKETS_AVAILABLE &&
      ( !queue_empty(order->queue) || !input.eof() ) ) {
    while( !input.eof() && order->tick_time <= order->current_time ) {
      order->get_order( input );
    }

    order->process_orders();

  }

  delete order->queue;
  delete order;

  return 0;
}


//
// get_file
// Open the file. If it exists and has content pass back input.
// Otherwise, exit the program with an appropriate error message.
//
void get_file( ifstream& input ) {
  // Read in file
  input.open(FILE_NAME);

  // When file could not be found
  if( input.fail() ) {
    cout << "Input file " << FILE_NAME << " does not exist. \n";
    exit(1);

  // When file is empty
  } else if( input.peek() == EOF ) {
    cout << "Input file " << FILE_NAME << " has no tickets to read. \n";
    exit(1);
  }
}

//
// get_orders
// Continue to read in orders until the tick time
// is greater than the current time. While  order
// into queue ever time it is read in and
//
void Order::get_order( ifstream& input ) {
  while( !input.eof() && tick_time <= current_time ) {

    cout << tick_time << "  " << current_time << endl;

    // Read in the order from the file
    input >> tick_time;
    tick_time += starting_time;

    input >> first_name;
    input >> last_name;
    input >> num_tickets;

    cout << first_name << endl;

    // Copy the order and send it to the queue
    Order *copied_order = new Order();
    copied_order = this;

    // Insert the order into the queue
    insert( queue, (void*)copied_order);

    // Close the file when at the end of file
    if( input.eof() ) input.close();

  }
}

//
// process_orders
// Process tickets
//
void Order::process_orders() {
  // Simulate sleep time
  sleep(SLEEP_TIME);
  current_time += SLEEP_TIME;

  if( queue_empty(queue) ) return;
  Order *queued_order = (Order*)queue->first->data;

  if( queued_order->tick_time <= current_time ) {

    if( (queued_order->num_tickets + num_tickets_used) < NUM_TICKETS_AVAILABLE ) {
      cout << "option1" << endl;
      print_orders();
    } else {
      cout << "options2" << endl;
      // Give the customer as many tickets as possible
      queued_order->num_tickets -= num_tickets_used;
      print_orders();
    }
  }
}

//
// print_orders
// Print orders' time in 00:00:00 format
// last name, first name, and number of tickets requested
//
void Order::print_orders() {
  Order *processed_order = (Order*)remove(queue);

  time_t diff = current_time - starting_time;
  time( &diff );
  tm *time_elapsed = localtime( &diff );

  cout << time_elapsed->tm_hour << ":"
       << time_elapsed->tm_min << ":"
       << time_elapsed->tm_sec << " - "
       << "Order " << confirmation_number << ": "
       << processed_order->last_name << ", "
       << processed_order->first_name << " "
       << "(" << processed_order->num_tickets << ") tickets" << endl;

  confirmation_number++;

  // Insert back on queue if order has tickets still not processed
  if( num_tickets_used == NUM_TICKETS_AVAILABLE ) {
    insert( queue, (void*)processed_order);
  }
}

//
// sold_out
// Print all the orders that could not be processed.
// Remove the order from the queue after printing the order.
//
void Order::sold_out() {
  while( !queue_empty(queue) ) {
    Order *order_data = (Order*)remove(queue);

    time_t diff = current_time - starting_time;
    time( &diff );
    tm *tm_time = localtime( &diff );

    cout << tm_time->tm_hour << ":"
         << tm_time->tm_min << ":"
         << tm_time->tm_sec
         << " - Tickets sold out --> Unable to process "
         << order_data->last_name << " "
         << order_data->first_name << "("
         << order_data->num_tickets << ")"
         << order_data->num_tickets << endl;

    confirmation_number++;

  }
}

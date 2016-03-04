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
  bool all_tickets_processed = false;
  Order *order = new Order();
  order->queue = newQueue();
  ifstream input;
  get_file( input );

  order->confirmation_number = 1;
  order->starting_time = time(0);
  order->current_time = time(0);

  while(!all_tickets_processed) {
    // order->current_time += time(0);

    if( order->get_order(input) ) {

      Order *copied_order = new Order();
      copied_order = order;

      if( order->tick_time <= order->current_time ) {
        insert( order->queue, (void*)copied_order);
        order->process_orders();
      } else {
        while( order->tick_time > order->current_time && !queue_empty(order->queue) ) {
          cout << "Ever while enough?" << endl;
          insert( order->queue, (void*)copied_order);
          order->process_orders();
        }
      }
    }

    if( order->num_tickets_used == NUM_TICKETS_AVAILABLE || input.eof() ) {
      if( queue_empty( order->queue ) ) {
        order->sold_out();
        all_tickets_processed = true;
      } else {
        while( !queue_empty(order->queue) ) {
          order->process_orders();
        }
      }
    }

  }

  input.close();

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
// Read the orders into a the order structure.
//
bool Order::get_order( ifstream& input ) {
  if( input.eof() ) return false;

  input >> tick_time;
  tick_time += starting_time;

  input >> first_name;
  input >> last_name;
  input >> num_tickets;

  return true;

}

//
// process_orders
// Process tickets
//
void Order::process_orders() {

  sleep(SLEEP_TIME);
  current_time += SLEEP_TIME;

  Order *queued_order = (Order*)queue->first->data;

  if( queued_order->tick_time > current_time ) return;

  if( (queued_order->num_tickets + num_tickets_used) < NUM_TICKETS_AVAILABLE ) {
    cout << "first" << endl;
    print_orders();
  } else {
    cout << "second" << endl;
    queued_order->num_tickets -= NUM_TICKETS_AVAILABLE;
    // Print as many orders as possible
    print_orders();
  }

}

//
// print_orders
// Print orders' time in 00:00:00 format
// last name, first name, and number of tickets requested
//
void Order::print_orders() {
  cout << "Print orders" << endl;

  // Order *processed_order = (Order*)queue->last;
  Order *processed_order = (Order*)remove(queue);
  cout << "Processed?" << endl;

  time_t diff = current_time - starting_time;
  time( &diff );
  tm *tm_time = localtime( &diff );

  // Timestamp - Order confirmation-number: last-name, first-name (number-of-tickets) tickets
  cout << tm_time->tm_hour << ":"
       << tm_time->tm_min << ":"
       << tm_time->tm_sec << " - "
       << "Order " << confirmation_number << ": "
       << processed_order->last_name << ", "
       << processed_order->first_name << " "
       << "(" << num_tickets << ") tickets" << endl;

  confirmation_number++;

  if( num_tickets_used == NUM_TICKETS_AVAILABLE ) sold_out();
}

//
// sold_out
// Print all the orders that could not be processed.
// Remove the order from the queue after printing the order.
//
void Order::sold_out() {
  cout << "Print sold out" << endl;

  while( queue->last != NULL ) {
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

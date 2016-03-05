//
// tickets.cpp
// Written by: Aaron Barlow
// 03/4/2016
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
  // Instantiate order and queue
  Order *order = new Order();
  order->queue = newQueue();

  // Get the file
  ifstream input;
  get_file( input );

  // Confirmation number must start at 1
  order->confirmation_number = 1;
  // Config start and current time
  order->starting_time = time(0);
  order->current_time = time(0);
  order->num_tickets_used = 0;
  // Set dummy tick_time to compare with current time
  order->tick_time = order->current_time;

  // Continue to simulate processing the tickets until all tickets are processed
  while( order->num_tickets_used != NUM_TICKETS_AVAILABLE &&
      ( !queue_empty(order->queue) || !input.eof() ) ) {

    // Simulate getting orders from file
    order->get_orders( input );

    // Simulate processing the order
    order->process_order();
  }

  // Delete dynamically allocated memory
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
void Order::get_orders( ifstream& input ) {
  while( !input.eof() && tick_time <= current_time ) {

    // Read in the order from the file
    input >> tick_time;
    tick_time += starting_time;

    input >> first_name;
    input >> last_name;
    input >> num_tickets;

    // Copy the vital order objects
    Order *copied_order = new Order();
    copied_order->first_name  = first_name;
    copied_order->last_name   = last_name;
    copied_order->tick_time   = tick_time;
    copied_order->num_tickets = num_tickets;

    // Insert the copied order into the queue
    insert( queue, (void*)copied_order);

    // Close the file once when at the end of file
    if( input.eof() ) input.close();

  }
}

//
// process_order
// Simulate time passing and then ensure queue is not empty.
// When the tick time is less than current time, read that order
// in and then print it.
//
void Order::process_order() {
  // Simulate sleep time
  sleep(SLEEP_TIME);
  current_time += SLEEP_TIME;

  // Check if there are any orders to process
  if( queue_empty(queue) ) return;
  Order *queued_order = (Order*)queue->first->data;

  if( queued_order->tick_time <= current_time ) {

    if( (queued_order->num_tickets + num_tickets_used) < NUM_TICKETS_AVAILABLE ) {
      num_tickets_used += queued_order->num_tickets;
      print_order();
      remove(queue);
    } else {
      int tickets_processed = 0;
      int tickets_not_processed = queued_order->num_tickets;

      // Determine number of tickets that can and can not be processed
      while( num_tickets_used < NUM_TICKETS_AVAILABLE ) {
        num_tickets_used++;
        tickets_processed++;
      }

      // Give the customer as many tickets as possible
      queued_order->num_tickets = tickets_processed;
      print_order();
      // Then inform all customers that orders can not be processed
      queued_order->num_tickets = tickets_not_processed - tickets_processed;
      sold_out();
    }
  }
}

//
// print_order
// Print orders' time in 00:00:00 format, last name,
// first name, and number of tickets requested.
// Put order back on queue when the there are no more tickets.
//
void Order::print_order() {
  // Ensure there is something in the queue to work with
  if( queue_empty(queue) ) return;

  Order *processed_order = (Order*)queue->first->data;

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
         << order_data->first_name << " request for ("
         << order_data->num_tickets << ") tickets" << endl;

    delete order_data;

  }

  cout << "Tickets are sold out and any future tickets will not be processed." << endl;
}

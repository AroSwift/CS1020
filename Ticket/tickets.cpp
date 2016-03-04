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

    if( !input.eof() ) {
      input >> order->tick_time;
      order->tick_time += order->starting_time;

      input >> order->first_name;
      input >> order->last_name;
      input >> order->num_tickets;

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

    // Simulate proccessing orders
    // order->get_orders();

    // If ticket time is equal to
    //  or less than current time, set that in queue

    // order->process_orders();

    if( order->num_tickets_used == NUM_TICKETS_AVAILABLE || input.eof() ) {
      if( queue_empty( order->queue ) ) {
        cout << "Sold out... " << endl;
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
void Order::get_orders() {
  ifstream input;

  cout << "Get orders" << endl;

  // Open and validate file exists as well as contains content
  get_file( input );

  // ticktime first-name last-name number-of-tickets
  while( !input.eof() ) {

    // sleep(SLEEP_TIME);
    // current_time = starting_time + SLEEP_TIME;

    input >> tick_time;
    tick_time += starting_time;

    cout << "Tick Time: " << tick_time << " Current Time: " << current_time << endl;

    input >> first_name;
    input >> last_name;
    input >> num_tickets;

    Order *copied_order = new Order();
    copied_order = this;

    if( tick_time <= current_time ) {
      insert( this->queue, (void*)copied_order);
      process_orders();
    } else {
      while( tick_time > current_time ) {
        sleep(SLEEP_TIME);
        // current_time += time(0);
        current_time = starting_time + SLEEP_TIME;
        process_orders();
      }
      insert( this->queue, (void*)copied_order);
    }

    if( num_tickets_used == NUM_TICKETS_AVAILABLE && queue_empty( queue ) ) {
      cout << "Sold out... " << endl;
      sold_out();
    }

  }

  input.close();

}

//
// process_orders
// Process tickets
//
void Order::process_orders() {

  sleep(SLEEP_TIME);
  current_time += SLEEP_TIME;

  cout << "Process orders " << endl;

  Order *queued_order = (Order*)queue->first->data;
  cout << queued_order->first_name << endl;

    cout << "tick > starting" << endl;
    cout << queued_order->tick_time << "  " << current_time << endl;

  if( queued_order->tick_time > current_time ) return;

  if( (queued_order->num_tickets + num_tickets_used) < NUM_TICKETS_AVAILABLE ) {
    cout << "first" << endl;
    print_orders();
  } else {
    cout << "second" << endl;
    queued_order->num_tickets -= NUM_TICKETS_AVAILABLE;
    // Print as many orders as possible
    print_orders();
    sold_out();
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

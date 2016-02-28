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
#include <thread>
#include "tickets.h"
using namespace std;

int main() {
  bool tickets_available = true
  Queue order_queue = newQueue();
  Order order = new Order();

  while(tickets_available) {
    order.get_orders();
    order.print_orders();

    sleep(SLEEP_TIME);
    // Then get tickets
    // Process tickets
    // If ticket time is equal to
    //  or less than current time, set that in queue
  }

  return 0;
}


void Order::get_orders() {
  ifstream input;

  // Read in file
  input.open(FILE_NAME);

  // When file could not be found
  if( input.fail() ) {
    cout << "Input file " << filename << " does not exist. \n";
    exit(1);

  // When file is empty
  } else if( input.peek() == EOF ) {
    cout << "Input file " << filename << " is empty. \n";
    exit(1);
  }


  // ticktime first-name last-name number-of-tickets
  while( !input.eof() ) {

    // Get sleep start time from HH:MM format
    string hours, minutes, seconds;
    getline( input, hours, ':' );
    getline( input, minutes, ':' );
    getline( input, seconds );

    string first_name, last_name;
    getline( input, first_name );
    getline( input, last_name );


    getline( input, num_tickets );

    // Convert strings to integers for date
    sleep[row].date.month = stoi(hours);
    sleep[row].date.day = stoi(minutes);
    sleep[row].date.year = stoi(seconds);


    // sleep[row].set_sleep_amount();

  }


  input.close();

}

void Order::print_orders(  ) {
  // if( q->front == NULL || q->rear == NULL) do stuff

  do {
    cout << order << endl;

  } while(order->next != NULL);
}



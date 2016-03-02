#pragma once
//
// queue.h
// Written by: Aaron Barlow
// 02/28/2016
//
// Header file for ticket processing program.
//

#include <string>
#include "queue.h"
using namespace std;

const char FILE_NAME[] = "tickets.dat";
const int NUM_TICKETS_AVAILABLE = 100;

// Number of seconds multiplied to get milliseconds
const int SLEEP_TIME = 10 * 1000;


struct Order {
  int current_tick_time;
  int tick_time;
  int confirmation_number;
  int num_tickets;
  string first_name;
  string last_name;

  // Methods
  void get_orders( Queue *q );
  void print_orders( Queue *q );
};


void validate_file( ifstream& input );

// 1. sort data before pushing
// 2. put onto queue
// 3. Deal with data
// 4. Print all

// If all tickets sold
  // Remove all from queue
  // Print each persons ticket



#pragma once
//
// queue.h
// Written by: Aaron Barlow
// 03/3/2016
//
// Header file for constants, order struct,
// and prototypes for ticket processing program.
//

#include <string>
#include "queue.h"
using namespace std;

// Constants
const char FILE_NAME[] = "tickets.dat";
const int NUM_TICKETS_AVAILABLE = 4;
const int SLEEP_TIME = 3;

// Order structure
struct Order {
  Queue *queue;
  time_t starting_time;
  time_t current_time;
  time_t tick_time;
  int confirmation_number;
  int num_tickets;
  int num_tickets_used;
  string first_name;
  string last_name;

  // Methods
  void get_orders( ifstream& input );
  void process_order();
  void print_order();
  void sold_out();
};

void get_file( ifstream& input );

#pragma once
//
// queue.h
// Written by: Aaron Barlow
// 02/28/2016
//
// Header file for ticket processing program.
//

#include <chrono>
#include "queue.c"

const FILE_NAME char[] = "tickets.dat";
const int NUM_TICKETS_AVAILABLE = 100;
// Number of seconds multiplied to get milliseconds
// const int SLEEP_TIME = 10 * 1000;
const int SLEEP_TIME = chrono(10);

class Order {
  public:
    // methods
    void get_orders();
    void print_orders();
  private:
    // class objects
    int confirmation_number;
    string first_name;
    string last_name;
    int num_tickets;
    int confirmation_order;
};

// 1. sort data before pushing
// 2. put onto queue
// 3. Deal with data
// 4. Print all

// If all tickets sold
  // Remove all from queue
  // Print each persons ticket
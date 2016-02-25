#pragma once

const FILE_NAME char[] = "tickets.dat";
const int NUM_TICKETS_AVAILABLE = 100;
// Number of seconds multiplied to get milliseconds
const int SLEEP_TIME = 10 * 1000;

class Ticket {
  public:
    // methods
    void get_tickets();
    void print_tickets();
  private:
    // class objects
    int confirmation_number;
    string first_name;
    string last_name;
    int num_tickets;
    int confirmation_order;

};

// 1. sort data before pushing
// 2. push onto stack
// 3. Deal with stack
// 4. Print all

// If all tickets sold
  // Remove all from queue
  // Print each persons ticket
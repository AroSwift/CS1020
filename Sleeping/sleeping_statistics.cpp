/*
Name: Aaron Barlow
Date: sleeping_statistics.cpp
Description: Determine
*/

#include <iostream>
#include "functions.h"
using namespace std;


int main() {
  int num_records;
  SleepData sleep[MAX_NUM_SLEEP_STATISTICS];

  // Read a given file into an array of structures
  read_file( sleep, num_records );

  // Give the user a menu
  display_menu( sleep, num_records );

  return 0;
}




// put "#pragma once" at the top of .h filetypes
// g++ filename.cpp -o helloworld
// requires an array
// assume every record is on a new line
// All structures, constants, definitions, and function definitions go in .h
// seperate line for each record
// show only the SHORTEST OR LONGEST sleep time
// when searching first and last name only EXACT match by IF
// TESTING: less than 10, more than 10 and exact 10 records
// antisipate all possible outcomes


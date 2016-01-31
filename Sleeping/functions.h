#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;


const int MAX_NUM_SLEEP_STATISTICS = 10; // Max sleeping statistics to utilize
const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255

// Full date in MM-DD-YYYY format
struct FullDate {
  int month;
  int day;
  int year;
};

// Time in 24 hour HH:MM format
struct Time {
  int hour;
  int minute;
};

struct SleepData {
  string first_name;
  string last_name;
  FullDate date;
  Time start_time;
  Time end_time;
  Time amount;

  void determine_sleep_amount();
};



void get_file_name( char filename[] ) {
  cout << "Enter input file name: ";
  cin.getline( filename, MAX_FILE_LENGTH ); // Max file length on linux is 255
}

void read_file( SleepData sleep[], int& num_records ) {
  char filename[MAX_FILE_LENGTH];
  int row, file_errors = 0;
  ifstream input;

  do {
    file_errors = 0; // Rest the number of file errors

    get_file_name( filename );
    input.open( filename );

    // When file could not be found
    if( input.fail() ) {
      cout << "Input file " << filename << " does not exist. \n";
      file_errors++;

    // When file is empty
    } else if( input.peek() == EOF ) {
      cout << "Input file " << filename << " is empty. \n";
      file_errors++;
    }

  } while( file_errors != 0 );

  // Read file data into an array of structures
  for( row = 0; row < MAX_NUM_SLEEP_STATISTICS; row++ ) {

    // Get first and last name
    getline( input, sleep[row].first_name );
    getline( input, sleep[row].last_name );

    // Get date from MM-DD-YYYY format
    string month, day, year;
    getline( input, month, '-' );
    getline( input, day, '-' );
    getline( input, year );

    // Get sleep start time from HH:MM format
    string start_hour, start_minute;
    getline( input, start_hour, ':' );
    getline( input, start_minute );

    // Get sleep start time from HH:MM format
    string end_hour, end_minute;
    getline( input, end_hour, ':' );
    getline( input, end_minute  );

    // Convert strings to integers and set date
    sleep[row].date.month = stoi(month);
    sleep[row].date.day = stoi(day);
    sleep[row].date.year = stoi(year);

    // Convert strings to integers and set start time
    sleep[row].start_time.hour = stoi(start_hour);
    sleep[row].start_time.minute = stoi(start_minute);

    // Convert strings to integers and set end time
    sleep[row].end_time.hour = stoi(end_hour);
    sleep[row].end_time.minute = stoi(end_minute);

    sleep[row].determine_sleep_amount();

    // Exit loop when end of file
    if( input.peek() == EOF) {
      break;
    }
  }


  // for( int i = 0; i < row; i++ ) {
  //   cout << sleep[i].first_name << ", ";
  //   cout << sleep[i].last_name << ", ";

  //   cout << sleep[i].date.month << ", ";
  //   cout << sleep[i].date.day << ", ";
  //   cout << sleep[i].date.year << ", ";

  //   cout << sleep[i].start_time.hour << ", ";
  //   cout << sleep[i].start_time.minute << ", ";

  //   cout << sleep[i].end_time.hour << ", ";
  //   cout << sleep[i].end_time.minute << ", ";

  //   cout << sleep[i].amount.hour << ", ";
  //   cout << sleep[i].amount.minute << ", " << endl;
  // }

  // The number of sleeping statistics retrieved
  num_records = row;

  // Then inform user of success
  cout << "File successfully loaded." << endl;

  input.close();

}

void SleepData::determine_sleep_amount() {
  // Ensure that sleep amount is valid
  if( end_time.hour >= start_time.hour ) {
    amount.hour = end_time.hour - start_time.hour;
    amount.minute = abs(end_time.minute - start_time.minute);
  } else { // Sleep time is invalid
    amount.hour = 0;
    amount.minute = 0;
  }
}

void swap_sleep_data( SleepData& x, SleepData& y ){
  SleepData temp;
  temp = x;
  x = y;
  y = temp;
}

void search_by_name( SleepData sleep[], int num_records ) {
  string first_name;
  string last_name;

  // what to do in multiple cases of same first or last name? - just the first
  // lowercase for search to expand possible matches
  // search BY FIRST AND LAST NAME

  cout << "Enter a first name: ";
  cin >> first_name;

  cout << "Enter a last name: ";
  cin >> last_name;

  for( int i = 0; i < num_records; i++ ) {
    // Select the first instance of first and last name matching given values name
    if( sleep[i].first_name == first_name && sleep[i].last_name == last_name ) {
      cout << "" << endl; // display dat stuff
      break;
    }
  }

}

void display_longest_sleep_times( SleepData sleep[], int num_records ) {

  cout << "Date        Longest Sleep Times" << endl;
  cout << "-------------------------------" << endl;

  for( int row = 0; row < num_records; row++ ) {

    // Print sleep dates
    cout << left
         << sleep[row].date.month << "-"
         << sleep[row].date.day << "-"
         << sleep[row].date.year;

    // Print longest sleep times
    cout << setw(10) << right
         << sleep[row].amount.hour << ":"
         << sleep[row].amount.minute << endl;
  }

}

void display_shortest_sleep_times( SleepData sleep[], int num_records ) {

  cout << "Date       Shortest Sleep Times" << endl;
  cout << "-------------------------------" << endl;

  for( int row = 0; row < num_records; row++ ) {

    // Print sleep dates
    cout << left
         << sleep[row].date.month << "-"
         << sleep[row].date.day << "-"
         << sleep[row].date.year;

    // Print longest sleep times
    cout << setw(10) << right
         << sleep[row].amount.hour << ":"
         << sleep[row].amount.minute << endl;
  }

}

void longest_sleep_times( SleepData sleep[], int num_records ) {
  int top = 0;
  int min_index, i;

  // Numerically order each structure by the longest sleep times
  for( top = 0; top < num_records; top++ ) {
    min_index = top;
    for ( i = top+1; i < num_records; i++ ) {

      // Compare the sleeper's numerical position
      if( sleep[min_index].amount.hour < sleep[i].amount.hour ) {
        if( sleep[min_index].amount.minute < sleep[i].amount.minute ) {
          // Update the minimum index
          min_index = i;
        }
      }

    }

    // Swap the structures
    swap_sleep_data( sleep[min_index], sleep[top] );

  }

  // print longest sleep times
  display_longest_sleep_times( sleep, num_records );

}

void shortest_sleep_times( SleepData sleep[], int num_records ) {
  int top = 0;
  int min_index, i;

  // Numerically order each structure by the shortest sleep times
  for( top = 0; top < num_records; top++ ) {
    min_index = top;
    for ( i = top+1; i < num_records; i++ ) {

      // Compare the sleeper's numerical position
      if( sleep[min_index].amount.hour > sleep[i].amount.hour ) {
        if( sleep[min_index].amount.minute > sleep[i].amount.minute ) {
          // Update the minimum index
          min_index = i;
        }
      }

    }

    // Swap the structures
    swap_sleep_data( sleep[min_index], sleep[top] );

  }

  // print shortest sleep times
  display_shortest_sleep_times( sleep, num_records );

}

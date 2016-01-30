#pragma once
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


const int MAX_NUM_SLEEP_STATISTICS = 10; // Max sleeping statistics to utilize
const int MAX_FILE_LENGTH = 256; // Max file length is 255
const string DEFAULT_ERROR_MESSAGE = "An error has occured. ";

struct FullDate {
  int month;
  int day;
  int year;
};

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
  // string date;
  // string sleep_start_time;
  // string sleep_end_time;
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

    // Get name
    getline( input, sleep[row].first_name );
    getline( input, sleep[row].last_name );

    // Get date
    string month, day, year;
    getline( input, month, '-' );
    getline( input, day, '-' );
    getline( input, year );

    // Get sleep start time
    string start_hour, start_minute;
    getline( input, start_hour, ':' );
    getline( input, start_minute );

    // Get sleep start time
    string end_hour, end_minute;
    getline( input, end_hour, ':' );
    getline( input, end_minute  );

    // Convert date objects to integers
    sleep[row].date.month = stoi(month);
    sleep[row].date.day = stoi(day);
    sleep[row].date.year = stoi(year);

    // Convert start time objects to integers
    sleep[row].start_time.hour = stoi(start_hour);
    sleep[row].start_time.minute = stoi(start_minute);

    // Convert end time objects to integers
    sleep[row].end_time.hour = stoi(end_hour);
    sleep[row].end_time.minute = stoi(end_minute);

    // Exit loop when end of file
    if( input.peek() == EOF) {
      break;
    }
  }


  for( int i = 0; i < row; i++ ) {
    cout << sleep[i].first_name << ", ";
    cout << sleep[i].last_name << ", ";

    cout << sleep[i].date.month << ", ";
    cout << sleep[i].date.day << ", ";
    cout << sleep[i].date.year << ", ";

    cout << sleep[i].start_time.hour << ", ";
    cout << sleep[i].start_time.minute << ", ";

    cout << sleep[i].end_time.hour << ", ";
    cout << sleep[i].end_time.minute << endl;
  }

  // The number of sleeping statistics retrieved
  num_records = row;

  // Then inform user of success
  cout << "File successfully loaded." << endl;

  input.close();

}



void search_by_name( SleepData sleep[], int num_records ) {
  string first_name;
  string last_name;

  // lowercase for search to expand possible matches
  // search BY FIRST AND LAST NAME

  cout << "Enter a first name: ";
  cin >> first_name;

  cout << "Enter a last name: ";
  cin >> last_name;

  for( int i = 0; i < num_records; i++ ) {
    if( sleep[i].first_name == first_name && sleep[i].last_name == last_name ) {
      cout << "" << endl; // display dat stuff
      break;
    }
  }

}


void swap_data( SleepData& x, SleepData& y ){
  SleepData temp;
  temp = x;
  x = y;
  y = temp;
}



// what to do in multiple cases of same first or last name? - just the first
// can i use constants? -YES
// What is the best way to break up my files?-ONLY ONE .H FILE


void longest_sleep_times( SleepData sleep[], int num_records ) {
  int top = 0;
  int min_index, i;

  // break it up using c_str
  // compare using to_i or equivalent

  // Alphabetical order each structure by their county name
  for( top = 0; top < num_records; top++ ) {
    min_index = top;
    for ( i = top+1; i < num_records; i++ ) {
      // Compare the county name’s alphabetical position
      // if( sleep[min_index].name == sleep[i].name ) {
      //   // Update the minimum index
      //   min_index = i;
      // }

    }

    // Swap the structures
    swap_data( sleep[min_index], sleep[top] );

  }

}


void shortest_sleep_times( SleepData sleep[], int num_records ) {

  // break it up using c_str
  // compare using to_i or equivalent

}




void display_menu( SleepData sleep[], int num_records ) {
  int choice;

  do {

    // Get user choice
    cout << "MAIN MENU" << endl
    << "-----------------------------" << endl
    << "1.) Search by Name" << endl
    << "2.) See Longest Sleep Time(s)" << endl
    << "3.) See Shortest Sleep Times(s)" << endl
    << "4.) Exit Program" << endl
    << "Choice: ";
    cin >> choice;

    // Associate choice with an action
    switch(choice) {
      case 1: // Search by name
        search_by_name(sleep, num_records);
        break;

      case 2: // See longest sleep time(s)
        longest_sleep_times(sleep, num_records);
        break;

      case 3: // See shortest sleep time(s)
        shortest_sleep_times(sleep, num_records);
        break;

      case 4: // Exit program
        exit(1);
        break;

      default: // Error occured
        cout << DEFAULT_ERROR_MESSAGE << "Please enter a valid option.";
        break;
    }

  } while(choice != 4);

}

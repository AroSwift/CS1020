#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "functions.h"
using namespace std;

int main() {
  bool exit = false;
  char choice;

  // Instantiate and dynamically allocate an array of contacts
  int num_records = get_number_records();
  Contact *contact = new Contact[num_records];

  // Read a file into an array of contact structures
  read_file( contact );

  // Display a menu
  do {

    // Give user choices
    cout << "Main Menu" << endl
    << "------------------" << endl
    << "1.) Search" << endl
    << "2.) List all" << endl
    << "3.) Show first contact" << endl
    << "4.) Show last contact" << endl
    << "5.) Exit" << endl
    << "Choice: ";
    cin >> choice;

    // Associate choice with an action
    switch(choice) {
      case '1': // Search contacts
        search_contacts( contact, num_records );
        break;

      case '2': // List all contacts
        list_all_contacts( contact, num_records );
        break;

      case '3': // Show first contact
        display_first_contact( contact, num_records );
        break;

      case '4': // Show last contact
        display_last_contact( contact, num_records );
        break;

      case '5': // Exit program
        exit = true;
        break;

      default: // Error occured
        cout << "Please enter a valid option." << endl;
        break;
    }

  } while(!exit);

  // Delete dynamically allocated array of contact structures
  delete[] contact;

  return 0;
}


int get_number_records() {
  string line;
  int num_lines;
  ifstream input;
  input.open(FILE_NAME);

  for (num_lines = 0; getline(input, line); ++num_lines);
  input.close();

  return num_lines/3;
}

string lower_case( string value ) {
  // Lowercase each character in a given string
  for( int i = 0; i < strlen( value.c_str() ); i++ ) {
    value[i] = tolower( value[i] );
  }

  return value;
}

void read_file( Contact contact[] ) {
  ifstream input;
  input.open(FILE_NAME);

  // When file could not be found
  if( input.fail() ) {
    cout << "Input file contacts.dat does not exist." << endl;
    exit(1);

  // When file is empty
  } else if( input.peek() == EOF ) {
    cout << "Input file contacts.dat is empty." << endl;
    exit(1);
  }

  // Read file data into an array of structures
  while( !input.eof() ) {

    input >> contact->first_name;
    input >> contact->last_name;
    input >> contact->phone_number;

  }

  // Close file
  input.close();

}

void insert_first( Contact **first ) {
  // Contact *c = new Contact();
  // c->first_name = first_name;
  // c->last_name = last_name;
  // c->phone_number = phone_number;
  // c->next = NULL;

  // if (*first != NULL) {
  //   c->next = *first;
  // }

  // *first = c;
}



void search_contacts( Contact contact[], int num_records ) {
  bool person_found = false;
  string user_input;

  cout << "Enter :";
  cin >> user_input;

  // Lowercase user input
  user_input = lower_case(user_input);

  for( int row = 0; row < num_records && !person_found; row++ ) {
    // Select all instances of first or last name matching given input
    if( user_input == lower_case(contact[row].first_name) || user_input == lower_case(contact[row].last_name) ) {
      person_found = true;

      cout << "First Name    Last Name    Phone Number" << endl;
      cout << "----------------------------------------" << endl;

      // Print first name, last name, and phone number
      cout << contact[row].first_name;
      cout << setw(15) << right << contact[row].last_name;
      cout << setw(13) << right << contact[row].phone_number << endl;
    }
  }

  if(!person_found) cout << "No person was found." << endl;


}

void list_all_contacts( Contact contact[], int num_records ) {

}

void display_first_contact( Contact contact[], int num_records ) {

}

void display_last_contact( Contact contact[], int num_records ) {

}




// Menu
// Search: search for EVERY  instances



// 11. show all contact lists
// previous and next takes to next
// Don't allow user to go past end or begining
// I can have multiple .h or .cpp files
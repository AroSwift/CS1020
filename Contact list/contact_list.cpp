#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "functions.h"
using namespace std;


int main() {
  Contact *first = NULL;
  bool exit = false;
  char choice;

  // Read a file into an array of contact structures
  read_file();

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

    // Add a new line to maintain neat layout
    cout << endl;

    // Associate choice with an action
    switch(choice) {
      case '1': // Search contacts
        search_contacts( first );
        break;

      case '2': // List all contacts
        list_all_contacts( first );
        break;

      case '3': // Show first contact
        display_first_contact( first );
        break;

      case '4': // Show last contact
        display_last_contact( first );
        break;

      case '5': // Exit program
        exit = true;
        break;

      default: // Error occured
        cout << "Please enter a valid option." << endl;
        break;
    }

    // Add a new line to maintain neat layout
    cout << endl;

  } while(!exit);

  return 0;
}

string lower_case( string value ) {
  // Lowercase each character in a given string
  for( int i = 0; i < strlen( value.c_str() ); i++ ) {
    value[i] = tolower( value[i] );
  }

  return value;
}

void read_file() {
  ifstream input;
  input.open(FILE_NAME);

  // When file could not be found
  if( input.fail() ) {
    cout << "Input file " << FILE_NAME << " does not exist." << endl;
    exit(1);

  // When file is empty
  } else if( input.peek() == EOF ) {
    cout << "Input file " << FILE_NAME << " is empty." << endl;
    exit(1);
  }

  // Contact *first = NULL;

  // Read file data into an array of structures
  while( !input.eof() ) {
    string first_name, last_name, phone_number;
    input >> first_name;
    input >> last_name;
    input >> phone_number;

    // Create new contact
    Contact *contact = new Contact;
    contact = new_contact( first_name, last_name, phone_number );

  }

  // Close file
  input.close();

}

Contact *new_contact( string first_name, string last_name, string phone_number ) {
  Contact *c = new Contact;
  c->first_name   = first_name;
  c->last_name    = last_name;
  c->phone_number = phone_number;
  c->next         = NULL;

  // Sort contact alphabetically by first and last name
  sort_contacts( c );

  return c;
}

void sort_contacts( Contact *contact ) {
  // contact
}

Contact *get_next( Contact *current_node ) {
  if (current_node != NULL) {
    return(current_node->next);
  }
}

Contact *get_prev( Contact *current_node ) {
  if (current_node != NULL) {
    return(current_node->prev);
  }
}

void search_contacts( Contact *first ) {
  bool contact_found = false;
  string user_input;

  cout << "Enter first or last name: ";
  cin >> user_input;

  // Lowercase user input
  user_input = lower_case(user_input);

  cout << "First Name                    Last Name                     Phone Number" << endl;
  cout << "------------------------------------------------------------------------" << endl;

  do {
    Contact *contact = get_next( first );


    // Select all instances of first or last name matching given input
    if( user_input == lower_case(contact->first_name) || user_input == lower_case(contact->last_name) ) {
      contact_found = true;

      // Print first name, last name, and phone number
      cout << setw(30) << left << contact->first_name;
      cout << setw(30) << left << contact->last_name;
      cout << setw(30) << left << contact->phone_number << endl;
    }

  } while( first != NULL );

  if(!contact_found) cout << "No contact was found." << endl;

}

void list_all_contacts( Contact *first ) {
  // cout << "First Name                    Last Name                     Phone Number" << endl;
  // cout << "------------------------------------------------------------------------" << endl;

  // for( int row = 0; row < num_records; row++ ) {
  //   // Print first name, last name, and phone number
  //   cout << setw(30) << left << contact[row].first_name;
  //   cout << setw(30) << left << contact[row].last_name;
  //   cout << setw(30) << left << contact[row].phone_number << endl;
  // }
}

void display_first_contact( Contact *first ) {

}

void display_last_contact( Contact *first ) {

}

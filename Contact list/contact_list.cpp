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

  // Set first and previous nodes to null
  Contact *first_node = NULL;
  Contact *prev_node  = NULL;

  // Read file data into an array of structures
  while( !input.eof() ) {
    string first_name, last_name, phone_number;
    input >> first_name;
    input >> last_name;
    input >> phone_number;

    // Create new contact and set new previous node to current node for next iteration
    Contact *prev_node = new_contact( prev_node, first_name, last_name, phone_number );

  }

  // Close file
  input.close();

}

Contact *new_contact( Contact *prev_node, string first_name, string last_name, string phone_number ) {
  Contact *c = new Contact;
  c->first_name   = first_name;
  c->last_name    = last_name;
  c->phone_number = phone_number;
  c->prev         = prev_node;
  c->next         = NULL;

  return c;
}

Contact *traverse_forward( Contact *first ) {
  Contact *node = first;
  while(node->next != NULL) {
    node = node->next;
  }

  return(node);
}

Contact *traverse_backward( Contact *first ) {
  Contact *node = first;
  while(node->prev != NULL) {
    node = node->prev;
  }

  return(node);
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
  cout << "First Name                    Last Name                     Phone Number" << endl;
  cout << "------------------------------------------------------------------------" << endl;

  // Set current node to point to head
  Contact *current_node = first;

  do {
    current_node = get_next( current_node );

    cout << setw(30) << left << current_node->first_name;
    cout << setw(30) << left << current_node->last_name;
    cout << setw(30) << left << current_node->phone_number << endl;

  } while( first != NULL );

}

void display_first_contact( Contact *first ) {
  cout << "First Name                    Last Name                     Phone Number" << endl;
  cout << "------------------------------------------------------------------------" << endl;

  cout << setw(30) << left << first->first_name;
  cout << setw(30) << left << first->last_name;
  cout << setw(30) << left << first->phone_number << endl;
}

void display_last_contact( Contact *first ) {
  Contact *node = first;
  while(node->next != NULL) {
    node = node->next;
  }

  cout << "First Name                    Last Name                     Phone Number" << endl;
  cout << "------------------------------------------------------------------------" << endl;

  // Print last node's first name, last name, and phone number
  cout << setw(30) << left << node->first_name;
  cout << setw(30) << left << node->last_name;
  cout << setw(30) << left << node->phone_number << endl;

}

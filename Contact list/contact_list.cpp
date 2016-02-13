//
// Name: Aaron Barlow
// Date: 2/12/2016
// Description: Read in a file and link the contacts via doubly linked list.
// Give the user the options to search, list all, show first contact in list,
// show last contact in list, and exit.
// With first and last contact, all user to traverse the doubly linked list
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "functions.h"
using namespace std;


int main() {
  // Set default end points of a doubly linked list
  Contact *first = NULL, *last = NULL;

  // Read a file into dynamically linked contact structures
  read_file( &first, &last );

  // Alphabetically sort the contact list
  sort_contacts( &first, &last );

  // Display the main menu
  main_menu( &first, &last );

  return 0;
}


void main_menu( Contact **first, Contact **last ) {
  bool exit = false;
  char choice;

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
        cout << endl;
        search_contacts( *first );
        cout << endl;
        break;

      case '2': // List all contacts
        cout << endl;
        list_all_contacts( *first );
        cout << endl;
        break;

      case '3': // Show first contact
        cout << endl;
        display_first_contact( *first );
        cout << endl;
        break;

      case '4': // Show last contact
        cout << endl;
        display_last_contact( *last );
        cout << endl;
        break;

      case '5': // Exit program
        exit = true;
        break;

      default: // Error occured
        cout << "Please enter a valid option." << endl;
        break;
    }

  } while(!exit);
}

string lower_case( string value ) {
  // Lowercase each character in a given string
  for( int i = 0; i < strlen( value.c_str() ); i++ ) {
    value[i] = tolower( value[i] );
  }

  return value; // As a lowercased string
}

void read_file( Contact **first, Contact **last ) {
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

  // Set previous node to point to first
  Contact *prev_node = *first;

  // Read file data into dynamically allocated structures
  while( !input.eof() ) {
    string first_name, last_name, phone_number;
    input >> first_name;
    input >> last_name;
    input >> phone_number;

    // Create new contact and set new previous node to current node for next iteration
    prev_node = new_contact( prev_node, first_name, last_name, phone_number );

    // When first points to null set first to the first contact in the list
    if( *first == NULL ) *first = prev_node;

  }

  // Set last node to point to the last contact in the list
  *last = prev_node;

  // Close file
  input.close();

}

Contact *new_contact( Contact *prev_node, string first_name, string last_name, string phone_number ) {
  // Instantiate a new instance of Contact and dynamically allocate it
  Contact *c = new Contact;
  c->first_name   = first_name;
  c->last_name    = last_name;
  c->phone_number = phone_number;
  c->prev         = prev_node;

  // When contact does not have a previous contact to point to,
  // Set contact's previous next's pointer to point to current contact
  if( c->prev != NULL ) {
    c->prev->next = c;
  }

  return c;
}

void sort_contacts( Contact **first, Contact **last ) {
  Contact *current_contact = *first;
  bool still_sorting;

  do {

    still_sorting = false;
    current_contact = *first;

    while( current_contact->next != NULL ) {

      string first_name = lower_case(current_contact->first_name);
      string last_name  = lower_case(current_contact->last_name);

      string next_first_name = lower_case(current_contact->next->first_name);
      string next_last_name  = lower_case(current_contact->next->last_name);

      if( last_name >= next_last_name ) {
        if( first_name > next_first_name ) {
          still_sorting = true;

          swap( current_contact->first_name, current_contact->next->first_name );
          swap( current_contact->last_name, current_contact->next->last_name );
          swap( current_contact->phone_number, current_contact->next->phone_number );

        }

      }

      current_contact = get_next( current_contact );

    }

  } while( still_sorting );

}

Contact *get_next( Contact *current_contact ) {
  if (current_contact != NULL) {
    return(current_contact->next);
  } else { // No contact was found
    return NULL;
  }
}

Contact *get_prev( Contact *current_contact ) {
  if (current_contact != NULL) {
    return(current_contact->prev);
  } else { // No contact was found
    return NULL;
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

  // Set current contact to first
  Contact *current_contact = first;

  while( current_contact != NULL ) {

    string first_name = lower_case(current_contact->first_name);
    string last_name  = lower_case(current_contact->last_name);

    // Select all instances of first or last name matching given input
    // Check if user input matches first name or last name of contact
    if( first_name.find(user_input) != string::npos || last_name.find(user_input) != string::npos ) {
      contact_found = true;

      // Print contact first name, last name, and phone number
      cout << setw(30) << left << current_contact->first_name;
      cout << setw(30) << left << current_contact->last_name;
      cout << setw(30) << left << current_contact->phone_number << endl;
    }

    // Find next contact for possible reiteration
    current_contact = get_next( current_contact );

  }

  if(!contact_found) cout << "No contact was found." << endl;

}

void list_all_contacts( Contact *first ) {
  // Return to menu when no records
  if( first == NULL ) {
    cout << "There are no contacts.";
    return;
  }

  cout << "First Name                    Last Name                     Phone Number" << endl;
  cout << "------------------------------------------------------------------------" << endl;

  // Set current node to point to head
  Contact *current_contact = first;

  do { // Print each contact data

    if( current_contact != NULL ) {
      // Print contact first name, last name, and phone number
      cout << setw(30) << left << current_contact->first_name;
      cout << setw(30) << left << current_contact->last_name;
      cout << setw(30) << left << current_contact->phone_number << endl;
    }

    // Get next contact for possible reiteration
    current_contact = get_next( current_contact );

  } while( current_contact != NULL );

}

void traverse_menu( Contact *current_contact ) {
  Contact *prev_contact, *next_contact;
  bool exit = false;

  // Print the first contact given
  display_contact( current_contact );

  do {
    cout << endl; // Extra endline to maintain a neat layout

    cout << "1. Previous" << endl;
    cout << right << "2. Next" << endl;
    cout << right << "3. Return to main menu" << endl;
    cout << "Choice: ";
    char choice;
    cin >> choice;

    cout << endl; // Extra endline to maintain a neat layout

    // Associate choice with an action
    switch(choice) {
      case '1': // Get previous contact (if possible)
        prev_contact = get_prev( current_contact );

        if( prev_contact == NULL ) {
          cout << "No contact was found." << endl;
        } else { // Contact was found
          // Set contact to point to previous contact for possible reiteration
          current_contact = prev_contact;
          // Print contact first name, last name, and phone number
        }
        display_contact( current_contact );
        break;

      case '2': // Get next contact (if possible)
        next_contact = get_next( current_contact );

        if( next_contact == NULL ) {
          cout << "No contact was found." << endl;
        } else { // Contact was found
          // Set contact to point to next contact for possible reiteration
          current_contact = next_contact;
          // Print contact first name, last name, and phone number
          display_contact( current_contact );
        }
        break;

      case '3': //Exit traverse menu
        // Indicate to loop to end and return to main menu
        exit = true;
        break;

      default: // If invalid input was entered
        cout << "Please enter a valid option." << endl;
        break;
    }

  } while(!exit);

}

void display_contact( Contact *contact ) {
  cout << "First Name                    Last Name                     Phone Number" << endl;
  cout << "------------------------------------------------------------------------" << endl;

  // Print first name, last name, and phone number
  cout << setw(30) << left << contact->first_name;
  cout << setw(30) << left << contact->last_name;
  cout << setw(30) << left << contact->phone_number << endl;
}

void display_first_contact( Contact *first ) {
  // Return to menu when no records
  if( first == NULL ) {
    cout << "There are no contacts.";
    return;
  }

  // Display traverse menu
  traverse_menu( first );

}

void display_last_contact( Contact *last ) {
  // Return to menu when no records
  if( last == NULL ) {
    cout << "There are no contacts.";
    return;
  }

  // Find last contact
  Contact *contact = last;
  while(contact->next != NULL) {
    contact = contact->next;
  }

  // Display traverse menu
  traverse_menu( last );

}

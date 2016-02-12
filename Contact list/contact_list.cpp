#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include "functions.h"
using namespace std;


int main() {
  // Set default first and last contact pointers of list
  Contact *first = NULL, *last = NULL;
  bool exit = false;
  char choice;

  // Read a file into dynamically linked contact structures
  read_file( &first, &last );

  // Sort the contact alphabetically
  sort_contacts( &first, &last );

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
        search_contacts( first );
        cout << endl;
        break;

      case '2': // List all contacts
        cout << endl;
        list_all_contacts( first );
        cout << endl;
        break;

      case '3': // Show first contact
        cout << endl;
        display_first_contact( first );
        cout << endl;
        break;

      case '4': // Show last contact
        cout << endl;
        display_last_contact( last );
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

  return 0;
}

string lower_case( string value ) {
  // Lowercase each character in a given string
  for( int i = 0; i < strlen( value.c_str() ); i++ ) {
    value[i] = tolower( value[i] );
  }

  return value;
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

  // Set previous node to point to first which points to null
  Contact *prev_node = *first;

  // Read file data into dynamically allocated structures
  while( !input.eof() ) {
    string first_name, last_name, phone_number;
    input >> first_name;
    input >> last_name;
    input >> phone_number;

    // Create new contact and set new previous node to current node for next iteration
    prev_node = new_contact( prev_node, first_name, last_name, phone_number );

    if( *first == NULL ) {
      *first = prev_node;
    }

  }

  *last = prev_node;

  // Close file
  input.close();

}

Contact *new_contact( Contact *prev_node, string first_name, string last_name, string phone_number ) {
  Contact *c = new Contact;
  c->first_name   = first_name;
  c->last_name    = last_name;
  c->phone_number = phone_number;
  c->prev         = prev_node;

  if( c->prev != NULL ) {
    c->prev->next = c;
  }

  return c;
}

void switch_contacts( Contact **c1, Contact **c2 ) {
  Contact *temp = *c1;

  *c1 = *c2;
  *c2 = temp;
}

void sort_contacts( Contact **first, Contact **last ) {
  Contact *current_contact = *first;
  bool sorting = true, nothing_sorted;
  int times = 0;

  cout << (*first)->first_name << endl;
  cout << (*first)->last_name << endl << endl;

  while( sorting ) {

    nothing_sorted = true;

    while( current_contact->next != *last ) {

      if( current_contact->next == NULL ) break;
      string first_name = lower_case(current_contact->first_name);
      string last_name  = lower_case(current_contact->last_name);

      string next_first_name = lower_case(current_contact->next->first_name);
      string next_last_name  = lower_case(current_contact->next->last_name);

      // if( last_name == next_last_name && first_name > next_first_name ) {

      //   cout << "Before: " << endl;
      //   cout << current_contact->first_name << endl;
      //   cout << current_contact->last_name << endl << endl;

      //   switch_contacts( &current_contact, &current_contact->next );

      //   nothing_sorted = false;

      //   cout << "After: " << endl;
      //   cout << current_contact->first_name << endl;
      //   cout << current_contact->last_name << endl << endl;
      if( last_name > next_last_name ) {

        cout << "Before: " << endl;
        cout << current_contact->first_name << endl;
        cout << current_contact->last_name << endl << endl;

        switch_contacts( &current_contact, &current_contact->next );
        nothing_sorted = false;
        *first = current_contact;

        cout << "After: " << endl;
        cout << current_contact->first_name << endl;
        cout << current_contact->last_name << endl << endl;
      }

      current_contact = get_next( current_contact );

    }

    times++;
    cout << times << endl;
    cout << "---------" << endl;

    cout << (*first)->first_name << endl;
    cout << (*first)->last_name << endl << endl;

    if( nothing_sorted ) {
      sorting = false;
      current_contact = *first;
    }

  }

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

  // Set first contact to first
  Contact *contact = first;

  do {
    contact = get_next( contact );

    if( contact != NULL ) {
      string first_name = lower_case(contact->first_name);
      string last_name  = lower_case(contact->last_name);

      // Select all instances of first or last name matching given input
      if( first_name.find(user_input) != string::npos || last_name.find(user_input) != string::npos ) {
        contact_found = true;

        // Print first name, last name, and phone number
        cout << setw(30) << left << contact->first_name;
        cout << setw(30) << left << contact->last_name;
        cout << setw(30) << left << contact->phone_number << endl;
      }
    }

  } while( contact != NULL );

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

  do {

    if( current_contact != NULL ) {
      cout << setw(30) << left << current_contact->first_name;
      cout << setw(30) << left << current_contact->last_name;
      cout << setw(30) << left << current_contact->phone_number << endl;
    }

    // Get next contact
    current_contact = get_next( current_contact );

  } while( current_contact != NULL );

}

void traverse_menu( Contact *contact ) {
  Contact *prev_contact, *next_contact;
  bool exit = false;

  // Show the first contact given
  display_contact( contact );

  do {
    cout << endl; // Extra endline to maintain a neat layout

    cout << "1. Previous" << endl;
    cout << right << "2. Next" << endl;
    cout << right << "3. Return to main menu" << endl;
    cout << "Choice: ";
    char choice;
    cin >> choice;

    cout << endl; // Extra endline to maintain a neat layout

    switch(choice) {
      case '1':
        prev_contact = get_prev( contact );

        if( prev_contact == NULL ) {
          cout << "No contact was found." << endl;
        } else { // Contact was found
          // Set contact to previous contact for possible reiteration
          contact = prev_contact;
          display_contact( contact );
        }
        break;

      case '2':
        next_contact = get_next( contact );

        if( next_contact == NULL ) {
          cout << "No contact was found." << endl;
        } else { // Contact was found
          // Set contact to next contact for possible reiteration
          contact = next_contact;
          display_contact( contact );
        }
        break;

      case '3':
        exit = true;
        break;

      default:
        cout << "Please enter a valid option." << endl;
        break;
    }

  } while(!exit);

}

void display_first_contact( Contact *first ) {
  // Return to menu when no records
  if( first == NULL ) {
    cout << "There are no contacts.";
    return;
  }

  traverse_menu( first );

}

void display_last_contact( Contact *first ) {
  // Return to menu when no records
  if( first == NULL ) {
    cout << "There are no contacts.";
    return;
  }

  // Find last contact
  Contact *contact = first;
  while(contact->next != NULL) {
    contact = contact->next;
  }

  traverse_menu( first );

}

void display_contact( Contact *contact ) {
  cout << "First Name                    Last Name                     Phone Number" << endl;
  cout << "------------------------------------------------------------------------" << endl;

  // Print first name, last name, and phone number
  cout << setw(30) << left << contact->first_name;
  cout << setw(30) << left << contact->last_name;
  cout << setw(30) << left << contact->phone_number << endl;
}


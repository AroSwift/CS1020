//
// Name: Aaron Barlow
// Date: 2/12/2016
// Description: Read in a file and link the contacts via doubly linked list.
// Give the user the options to search, list all, show first contact in list,
// show last contact in list, and exit.
// With first and last contact, all user to traverse the doubly linked list
//

#pragma once
#include <iostream>
using namespace std;

// The name of the file that the contact data resides
const char FILE_NAME[] = "contacts.dat";

struct Contact {
  string  first_name;
  string  last_name;
  string  phone_number;
  Contact *prev, *next;
};

void read_file( Contact **first, Contact **last );
string lower_case( string value );

void sort_contacts( Contact **first, Contact **last );
void display_contact( Contact *contact );
Contact *get_next(Contact *current_contact);
Contact *get_prev(Contact *current_contact);
Contact *new_contact( Contact *prev_node, string first_name, string last_name, string phone_number );

void traverse_menu( Contact *contact );
void search_contacts( Contact *first );
void list_all_contacts( Contact *first );
void display_first_contact( Contact *first );
void display_last_contact( Contact *last );
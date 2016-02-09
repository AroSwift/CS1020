#pragma once
#include <iostream>
using namespace std;

const char FILE_NAME[] = "contacts.dat";

struct Contact {
  string  first_name;
  string  last_name;
  string  phone_number;
  Contact *prev, *next;
};


void traverse_menu( Contact *contact );
void read_file( Contact **first );
string lower_case( string value );

void display_contact( Contact *contact );
Contact *get_next(Contact *current_node);
Contact *get_prev(Contact *current_node);
Contact *new_contact( Contact *prev_node, string first_name, string last_name, string phone_number );

void search_contacts( Contact *first );
void list_all_contacts( Contact *first );
void display_first_contact( Contact *first );
void display_last_contact( Contact *first );
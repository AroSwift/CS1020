#pragma once
#include <iostream>
using namespace std;

const char FILE_NAME[] = "contacts.dat";

struct Contact {
  string  first_name;
  string  last_name;
  string  phone_number;
  Contact *prev;
  Contact *next;
};


void read_file();
string lower_case( string value );
void sort_contacts( Contact *contact );

Contact *get_next(Contact *current_node);
Contact *get_prev(Contact *current_node);
Contact *new_contact( string first_name, string last_name, string phone_number );

void search_contacts( Contact *first );
void list_all_contacts( Contact *first );
void display_first_contact( Contact *first );
void display_last_contact( Contact *first );
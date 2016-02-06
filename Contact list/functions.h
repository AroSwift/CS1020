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


int get_number_records();
string lower_case( string value );
void read_file( Contact contact[] );

void traverse( Contact *first );
void insert_first( Contact **first );

void search_contacts( Contact contact[], int num_records );
void list_all_contacts( Contact contact[], int num_records );
void display_first_contact( Contact contact[], int num_records );
void display_last_contact( Contact contact[], int num_records );
#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstdlib>
using namespace std;

struct Contact {
  string first_name;
  string last_name;
  string phone_number;
  Contact *prev;
  Contact *next;
};


void read_file( Contact contact[] );

void traverse( Contact *first );
void insert_first( Contact **first );

void search_contacts();
void list_all_contacts();
void display_first_contact();
void display_last_contact();


void read_file( Contact contact[] ) {
  ifstream input;
  input.open("contacts.dat");


  // When file could not be found
  if( input.fail() ) {
    cout << "Input file contacts.dat does not exist." << endl;
    exit(1);

  // When file is empty
  } else if( input.peek() == EOF ) {
    cout << "Input file contacts.dat is empty." << endl;
    exit(1);
  }

  // instantiate and dynamically allocate
  Contact* contact = new Contact[];

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
  Contact *c = new Contact();
  c->first_name = first_name;
  c->last_name = last_name;
  c->phone_number = phone_number;
  c->next = NULL;

  if (*first != NULL) {
    c->next = *first;
  }

  *first = c;
}



void search_contacts() {

}

void list_all_contacts() {

}

void display_first_contact() {

}

void display_last_contact() {

}

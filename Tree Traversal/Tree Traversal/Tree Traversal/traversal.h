#pragma once
#include <string>
#include "tree.h"
#include <string>
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255
const int NUM_OPTIONS = 6;

class Person {
public:
   Person() {};
   Person(string first_name, string last_name);
   Person( string first_name, string last_name, string street_address, string city, string state, string zip );
   void print_person_data();
   void search_for_person();
   friend ostream& operator<<(ostream& os, Person& p);
   friend bool compare_people(Person p1, Person p2);
   friend bool compare_equality(Person p1, Person p2);
private:
   string first_name;
   string last_name;
   string street_address;
   string city;
   string state;
   string zip;
};

Person::Person( string first_name, string last_name, string street_address, string city, string state, string zip ) {
   this->first_name = first_name;
   this->last_name = last_name;
   this->street_address = street_address;
   this->city = city;
   this->state = state;
   this->zip = zip;
}

Person::Person(string first_name, string last_name) {
   this->first_name = first_name;
   this->last_name = last_name;
}


string lower_case( string value );


bool compare_people(Person p1, Person p2) {
   return( (p2.last_name < p1.last_name) || ((p2.last_name == p1.last_name) && (p2.first_name < p1.first_name)) );
}

bool compare_equality(Person p1, Person p2) {
   string p1_first_name = lower_case(p1.first_name), p2_first_name = lower_case(p2.first_name);
   string p1_last_name = lower_case(p1.last_name), p2_last_name = lower_case(p2.last_name);
   return p1_first_name == p2_first_name && p1_last_name == p2_last_name;
}


void load_people(Tree<Person>* tree);
void search_for_person(Tree<Person>* tree);

// Menu Options
void main_menu(Tree<Person>* tree, char settings[]);
void options_menu(char settings[]);
void change_settings_menu(char settings[]);



#pragma once
#include "tree.h"
#include <string>
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255

class Person {
   string first_name;
   string last_name;
   string street_address;
   string city;
   string state;
   string zip;
public:
   Person();
   Person( string first_name, string last_name, string street_address, string city, string state, string zip );
//   ~Person();
   void print_person_data();
   void search_for_person();
   friend ostream& operator<<(ostream& os, Person& p);
   friend bool operator<(const Person& left, const Person& right);
   friend bool compare_people(Person p1, Person p2);
};

class Settings {
public:
   Settings();
   ~Settings();
private:
   bool can_show_first_name;
   bool can_show_last_name;
   bool can_show_street_address;
   bool can_show_city;
   bool can_show_state;
   bool can_show_zip;
};

Person::Person( string first_name, string last_name, string street_address, string city, string state, string zip ) {
   this->first_name = first_name;
   this->last_name = last_name;
   this->street_address = street_address;
   this->city = city;
   this->state = state;
   this->zip = zip;
}

Person::Person() {
}

// Person::~Person() {
//    delete Person;
// }


bool compare_people(Person p1, Person p2) {
   return((p2.last_name < p1.last_name) || ((p2.last_name == p1.last_name) && (p2.first_name < p1.first_name)));
}


ostream& operator<<(ostream& os, Person& p) {
   os << p.first_name << ", " << p.last_name;
   return os;
}

bool operator<(const Person& left, const Person& right) {
   return((left.last_name < right.last_name) || ((left.last_name == right.last_name) && (left.first_name < right.first_name)));
}

// Menu Options
void load_people(Tree<Person>* tree);
void main_menu(Tree<Person>* tree);
void options_menu(Tree<Person>* tree);

void search_for_person();


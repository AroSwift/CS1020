#pragma once
#include "tree.h"
#include <string>
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255

class Settings {
public:
   Settings();
   //   ~Settings();
   void set_settings( bool show_first_name, bool show_last_name, bool show_street_address, bool show_city, bool show_state, bool show_zip );
   void options_menu();
   void change_settings_menu();
private:
   bool prior_settings;
   bool can_show_first_name;
   bool can_show_last_name;
   bool can_show_street_address;
   bool can_show_city;
   bool can_show_state;
   bool can_show_zip;
};


class Person {
public:
   Person() {};
   Person( string first_name, string last_name, string street_address, string city, string state, string zip );
//   ~Person();
   void print_person_data();
   void search_for_person();
   friend ostream& operator<<(ostream& os, Person& p);
   friend bool compare_people(Person p1, Person p2);
private:
   string first_name;
   string last_name;
   string street_address;
   string city;
   string state;
   string zip;
};

Settings::Settings() {
    prior_settings = false;
    can_show_first_name = true;
    can_show_last_name = true;
    can_show_street_address = true;
    can_show_city = true;
    can_show_state = true;
    can_show_zip = true;
}

//Settings::~Settings() {
//   delete this;
//}

void Settings::set_settings(bool show_first_name, bool show_last_name, bool show_street_address, bool show_city, bool show_state, bool show_zip) {
    this->prior_settings = true;
    this->can_show_first_name = show_first_name;
    this->can_show_last_name = show_last_name;
    this->can_show_street_address = show_street_address;
    this->can_show_city = show_city;
    this->can_show_state = show_state;
    this->can_show_zip = show_zip;
}

Person::Person( string first_name, string last_name, string street_address, string city, string state, string zip ) {
   this->first_name = first_name;
   this->last_name = last_name;
   this->street_address = street_address;
   this->city = city;
   this->state = state;
   this->zip = zip;
}

// Person::~Person() {
//    delete Person;
// }


bool compare_people(Person p1, Person p2) {
   return((p2.last_name < p1.last_name) || ((p2.last_name == p1.last_name) && (p2.first_name < p1.first_name)));
}


ostream& operator<<(ostream& os, Person& p) {
   os << p.first_name << ", " << p.last_name;
//   if( can_show_first_name ) os << p.first_name;
   return os;
}

//bool operator<(const Person& left, const Person& right) {
//   return((left.last_name < right.last_name) || ((left.last_name == right.last_name) && (left.first_name < right.first_name)));
//}

void load_people(Tree<Person>* tree);

// Menu Options
void main_menu(Tree<Person>* tree, Settings *s);
void options_menu(Tree<Person>* tree, Settings *s);

void search_for_person();


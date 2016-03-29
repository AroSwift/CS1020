#pragma once
#include <string>
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
   Person(string first_name, string last_name);
   Person( string first_name, string last_name, string street_address, string city, string state, string zip );
//   ~Person();
   void print_person_data();
   void search_for_person();
   friend ostream& operator<<(ostream& os, Person& p);
   friend bool operator==(const Person& left, const Person& right);
   friend bool compare_people(Person p1, Person p2);
   friend bool compare_equality( Person p1, Person p2);
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

Person::Person(string first_name, string last_name) {
   this->first_name = first_name;
   this->last_name = last_name;
}


// Person::~Person() {
//    delete Person;
// }

string lower_case( string value );

void load_people(Tree<Person>* tree);
void search_for_person(Tree<Person>* tree);


// Menu Options
void main_menu(Tree<Person>* tree, Settings *s);
void options_menu(Tree<Person>* tree, Settings *s);


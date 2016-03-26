#pragma once
#include "tree.h"
#include <string>
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255

// main functions! AND CLAS FUNCTIONS

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
   ~Person();
   void print_person_data();
   void search_for_person();
   friend ostream& operator<<(ostream& os, Person& p);
   friend bool operator<(const Person& left, const Person& right);
};

Person::Person( string first_name, string last_name, string street_address, string city, string state, string zip ) {

}

// Person::~Person() {
//    delete Person;
// }


ostream& operator<<(ostream& os, Person& p) {
   os << p.first_name << ", " << p.last_name;
   return os;
}

bool operator<(const Person& left, const Person& right) {
   return((left.last_name < right.last_name) || ((left.last_name == right.last_name) && (left.first_name < right.first_name)));
}

void load_people(vector<Person> people, Tree<Person> tree);
void main_menu(vector<Person> people, Tree<Person> tree);

void choose_choices();
void search_for_person();
void print_person_data();


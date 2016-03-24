#pragma once
#include "tree.h"
#include <string>
using namespace std;

const int MAX_FILE_LENGTH = 256; // Max file length on linux is 255

// main functions! AND CLAS FUNCTIONS

class Person {
    friend class Accessable_Person;
    string first_name;
    string last_name;
    string street_address;
    string city;
    string state;
    string zip;
public:
    Person( string first_name, string last_name, string street_address, string city, string state, string zip );
    ~Person();
    void print_person_data();
    void search_for_person();
    string get_first_name();
    string get_last_name();
    
};

Person::Person( string first_name, string last_name, string street_address, string city, string state, string zip ) {


}

// Person::~Person() {
//    delete Person;
// }

string Person::get_first_name() {
    return first_name;
}

string Person::get_last_name() {
    return last_name;
}

ostream& operator<<(ostream& os, Person& p) {
    os << p.get_first_name() << ", " << p.get_last_name();
    return os;
}


void load_people(vector<Person> people);
void main_menu( vector<Person> people );

void choose_choices();
void search_for_person();
void print_person_data();


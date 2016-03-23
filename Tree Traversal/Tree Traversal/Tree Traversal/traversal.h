#pragma once
#include "tree.h"
#include <string>
using namespace std;

class Person {
    string first_name;
    string last_name;
    string street_address;
    string city;
    string state;
    string zip;
public:
    Person( string first_name, string last_name, string street_address, string city, string state, string zip );
//  ~Person();
    void print_person_data();
};



void search_by_name() {
    
}



void print_person_data() {
    
}
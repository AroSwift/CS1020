#pragma once
#include "tree.h"
#include <string>
using namespace std;

// main functions! AND CLAS FUNCTIONS


class Person {
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
};


Person::Person( string first_name, string last_name, string street_address, string city, string state, string zip ) {
    
}

Person::~Person() {
    delete Person();
}

//
// main_menu
//
void main_menu( Node *root_node ) {
    bool exit = false;
    char choice;
    
    // Display a menu
    do {
        
        // Give user choices
        cout << "Main Menu" << endl
        << "------------------" << endl
        << "1.) Pre-order traversal" << endl
        << "2.) In-order traversal" << endl
        << "3.) Post-order traversal" << endl
        << "4.) Breadth-first traversal" << endl
        << "5.) Search for a name"
        << "6.) Exit" << endl
        << "Choice: ";
        cin >> choice;
        
        // Associate choice with an action
        switch(choice) {
            case '1': // Pre-order traversal
                cout << endl;
                pre_order_traversal(root_node);
                cout << endl;
                break;
                
            case '2': // In-order traversal
                cout << endl;
                in_order_traversal(root_node);
                cout << endl;
                break;
                
            case '3': // Post-order traversal
                cout << endl;
                post_order_traversal(root_node);
                cout << endl;
                break;

            case '4': // Show last contact
                cout << endl;
                breadth_first_traversal(root_node));
                cout << endl;
                break;
                
            case '5': // Show last contact
                cout << endl;
                breadth_first_traversal(root_node));
                cout << endl;
                break;
                
            case '6': // Exit program
                exit = true;
                break;
                
            default: // Error occured
                cout << "Please enter a valid option." << endl;
                break;
        }
        
    } while(!exit);
}

void choose_choices() {
    
}


void search_for_person() {
    
}



void print_person_data() {
    
}




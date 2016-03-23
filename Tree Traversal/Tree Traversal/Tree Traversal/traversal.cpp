#include <iostream>
#include <fstream>
#include <vector>
#include "traversal.h"
using namespace std;

// if using templates do not need this

int main() {
    vector<Person> people;
    
    
}


void load_people(vector<Person> people) {
    ifstream input;
    char filename[MAX_FILE_LENGTH];
    bool file_errors;
    
    do { // Find a file that exists
        file_errors = false;
        
        // Prompt for file and read it in
        cout << "Enter file name: ";
        cin.getline( filename, MAX_FILE_LENGTH );
        
        input.open( filename );
        
        // When file could not be found
        if( input.fail() ) {
            cout << "Input file " << filename << " does not exist. \n";
            file_errors = true;
            
            // When file is empty
        } else if( input.peek() == EOF ) {
            cout << "Input file " << filename << " is empty. \n";
            file_errors = true;
        }
        
    } while( file_errors );

    
    input.open(FILE_NAME);
    
    // When file could not be found
    if( input.fail() ) {
        cout << "Input file " << FILE_NAME << " does not exist." << endl;
        exit(1);
        
        // When file is empty
    } else if( input.peek() == EOF ) {
        cout << "Input file " << FILE_NAME << " is empty." << endl;
        exit(1);
    }
    
    // Set previous node to point to first
    Contact *prev_node = *first;
    
    while( !input.eof() ) {
        string first_name, last_name, phone_number;
        input >> first_name;
        input >> last_name;
        input >> phone_number;
        
    }
    
    // Close file
    input.close();
    
}
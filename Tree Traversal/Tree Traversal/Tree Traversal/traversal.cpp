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


    // Read in file row by row
    for( int i = 0; i < people.size(); i++ ) {
        // Ensure null character is accounted for in file
        string first_name, last_name, street_address, city, state, zip;
        getline( input, first_name, ',' );
        getline( input, last_name, ',' );
        getline( input, street_address, ',' );
        getline( input, city, ',' );
        getline( input, state, ',' );
        getline( input, zip, ',' );
        
        people.push_back( Person(first_name, last_name, street_address, city, state, zip) );

    }

}
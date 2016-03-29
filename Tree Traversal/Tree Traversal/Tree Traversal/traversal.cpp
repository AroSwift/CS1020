#include <iostream>
#include <fstream>
#include <vector>
#include "traversal.h"
using namespace std;

int main() {
   Tree<Person>* tree = new Tree<Person>;
//   Settings *s = new Settings();
   char settings[NUM_OPTIONS];

   load_people(tree);

   // Show the menu
   main_menu(tree, settings);

   delete tree;

}

void load_people(Tree<Person>* tree) {
   ifstream input;
   char filename[MAX_FILE_LENGTH];
   bool file_errors;

   do { // Find a file that exists
      file_errors = false;

      // Prompt for file and read it in
      cout << "Enter file name: ";
      cin.getline( filename, MAX_FILE_LENGTH );

      // Attempt to open the filename the user gave
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


   // Read in file row by row while there is data to read in
   while( !input.eof() ) {
      // Read in the data that encompasses a person
      string first_name, last_name, street_address, city, state, zip;
      
      // Remove preceding whitespace with 'ws' if it is present,
      // But do not assume it will be by using getline delimiters
      input >> ws;
      getline( input, first_name, ',' );
      input >> ws;
      getline( input, last_name, ',' );
      input >> ws;
      getline( input, street_address, ',' );
      input >> ws;
      getline( input, city, ',' );
      input >> ws;
      getline( input, state, ',' );
      input >> ws;
      getline( input, zip, '\n' );

      // Instantiate a new person with the data read in
      Person *p = new Person(first_name, last_name, street_address, city, state, zip);

      // Then put this data in the tree
      tree->insert(*p, &compare_people);

   }

}



//
// main_menu
//
void main_menu(Tree<Person>* tree, char settings[]) {
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
      << "5.) Search for a name" << endl
      << "6.) Exit" << endl
      << "Choice: ";
      cin >> choice;

      // Associate choice with an action
      switch(choice) {
         case '1': // Pre-order traversal
            cout << endl;
            options_menu(settings);
            tree->pre_order_traversal();
            break;

         case '2': // In-order traversal
            cout << endl;
            options_menu(settings);
            tree->in_order_traversal();
            break;

         case '3': // Post-order traversal
            cout << endl;
            options_menu(settings);
            tree->post_order_traversal();
            break;

         case '4': // Breadth-order traversal
            cout << endl;
            options_menu(settings);
            tree->breadth_first_traversal();
            break;

         case '5': // Search for Name
            cout << endl;
            options_menu(settings);
            search_for_person(tree);
            break;

         case '6': // Exit program
            exit = true;
            break;

         default: // Error occured
            cout << "Please enter a valid option." << endl;
            cout << endl;
            break;
      }

   } while(!exit);
}

void options_menu(char settings[]) {
   if( strcmp(settings, "") == 0 ) {
      bool acceptable_input;
      do {
         char user_choice;
         cout << "Would you like to use your previous settings? (Y, N): ";
         cin >> user_choice;

         if( user_choice == 'Y' || user_choice == 'y' ) {
            acceptable_input = true;
            change_settings_menu(settings);
         } else if( user_choice == 'N' || user_choice == 'n' ) {
            acceptable_input = true;
         } else {
            cout << "Please enter 'Y' or 'N' to indicate whether you would like to use the prior settings." << endl;
            acceptable_input = false;
         }
      } while( !acceptable_input );
   } else {
      change_settings_menu(settings);
   }
}

void change_settings_menu(char settings[]) {
   string choice;

   // Display a menu
   
   // Give user choices
   cout << "Field Selection Menu" << endl
   << "-------------------------" << endl
   << "Please select which fields you would like to be displayed:" << endl
   << "1.) Show first name" << endl
   << "2.) Show last name" << endl
   << "3.) Show street address" << endl
   << "4.) Show city" << endl
   << "5.) Show state" << endl
   << "6.) Show zip" << endl
   << "Choice: ";
   cin >> choice;

      
   for( int i = 0, s = 0; i < choice.length(); i++ ) {
      if( isdigit(choice[i]) ) {
         if(choice[i] >= 1 || choice[i] <= 6) {
            if( strstr(settings, &choice[i]) ) settings[s++] = choice[i];
         }
      }
   }
   
   cout << endl;
   
}

void search_for_person(Tree<Person>* tree) {
   string first_name, last_name;
   
   cout << "Find a Person:" << endl
   << "-------------------" << endl;
   
   cout << "Enter the first name: ";
   cin >> first_name;
   
   cout << "Enter the last name: ";
   cin >> last_name;
   
   Person *search_person = new Person( first_name, last_name );
   
//   Person *found_person = new Person;
   
   tree->search(*search_person, &compare_equality);
   
}



//
// lower_case
// Lowercases all characters in a given string.
// Returns the lowercased string.
//
string lower_case( string value ) {
   // Lowercase each character in a given string
   for( int i = 0; i < strlen( value.c_str() ); i++ ) {
      value[i] = tolower( value[i] );
   }
   
   return value; // As a lowercased string
}

ostream& operator<<(ostream& os, Person& p) {
   os << p.first_name << ", " << p.last_name;
   return os;
}


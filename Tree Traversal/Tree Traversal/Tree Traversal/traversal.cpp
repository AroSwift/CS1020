#include <iostream>
#include <fstream>
#include <vector>
#include "traversal.h"
using namespace std;

// if using templates do not need this

int main() {
//   Tree<Person> tree;
   Tree<Person>* tree = new Tree<Person>;

   load_people(tree);

   // Show the menu
   main_menu(tree);


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
   while( !input.eof() ) {
      // Ensure null character is accounted for in file
      string first_name, last_name, street_address, city, state, zip;
      getline( input, first_name, ',' );
      getline( input, last_name, ',' );
      getline( input, street_address, ',' );
      getline( input, city, ',' );
      getline( input, state, ',' );
      getline( input, zip, '\n' );

      cout << first_name << " " << last_name << " " << street_address << " " << city << " " << state << " " << zip << endl;

      Person *p = new Person(first_name, last_name, street_address, city, state, zip);

      // put in the tree
      tree->insert(*p, &compare_people);

   }

}



//
// main_menu
//
void main_menu(Tree<Person>* tree) {
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
            tree->pre_order_traversal();
            break;

         case '2': // In-order traversal
            cout << endl;
            tree->in_order_traversal();
            break;

         case '3': // Post-order traversal
            cout << endl;
            tree->post_order_traversal();
            break;

         case '4': // Breadth-order traversal
            cout << endl;
            tree->breadth_first_traversal();
            break;

         case '5': // Search for Name
            cout << endl;
            search_for_person();
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

void choose_choices() {

}

void search_for_person() {

}

void print_person_data() {

}





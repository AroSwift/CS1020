#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "traversal.h"
using namespace std;

int main() {
   Tree<Person>* tree = new Tree<Person>;
//   Settings *s = new Settings();
   string settings;

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
void main_menu(Tree<Person>* tree, string settings) {
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
            pre_order_traversal(tree->get_root(), settings);
            break;

         case '2': // In-order traversal
            cout << endl;
            options_menu(settings);
            in_order_traversal(tree->get_root(), settings);
            break;

         case '3': // Post-order traversal
            cout << endl;
            options_menu(settings);
            post_order_traversal(tree->get_root(), settings);
            break;

         case '4': // Breadth-order traversal
            cout << endl;
            options_menu(settings);
            breadth_first_traversal(tree->get_root(), settings);
            break;

         case '5': // Search for Name
            cout << endl;
            options_menu(settings);
            search_for_person(tree, settings);
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

void options_menu(string &settings) {
   if( settings != "" ) {
      bool acceptable_input;
      do {
         char user_choice;
         cout << "Would you like to use your previous settings? (Y, N): ";
         cin >> user_choice;

         if( user_choice == 'Y' || user_choice == 'y' ) {
            acceptable_input = true;
         } else if( user_choice == 'N' || user_choice == 'n' ) {
            acceptable_input = true;
            change_settings_menu(settings);
         } else {
            cout << "Please enter 'Y' or 'N' to indicate whether you would like to use the prior settings." << endl;
            acceptable_input = false;
         }
      } while( !acceptable_input );
   } else {
      change_settings_menu(settings);
   }
}

void change_settings_menu(string &settings) {
   string choice;

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

   settings = choice;
   
   cout << endl;

}

//
// search
// Call the private method search
// and set the base case to root
// and pass the passed paramaters.
//
void search(Tree<Person>* tree, Person p, string settings) {
   Person *found_person = tree->search( tree->get_root(), p, &compare_equality, 1 );
   if(found_person == NULL) {
      // Inform user no record can be found when whole tree has been traversed
      cout << "The person could not be found." << endl << endl;
   } else {
      print_data(*found_person, settings);
   }
}


void search_for_person(Tree<Person>* tree, string settings) {
   string first_name, last_name;

   cout << "Find a Person:" << endl
   << "-------------------" << endl;

   cout << "Enter the first name: ";
   cin >> first_name;

   cout << "Enter the last name: ";
   cin >> last_name;

   Person *search_person = new Person( first_name, last_name );
   
   search(tree, *search_person, settings);
   
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


void print_data(Person p, string settings) {
   if( settings.find('1') != string::npos) cout << "First Name: " << p.first_name << endl;
   if( settings.find('2') != string::npos) cout << "Last Name: " << p.last_name << endl;
   if( settings.find('3') != string::npos) cout << "Street Address: " << p.street_address << endl;
   if( settings.find('4') != string::npos) cout << "City: " << p.city << endl;
   if( settings.find('5') != string::npos) cout << "State: " << p.state << endl;
   if( settings.find('6') != string::npos) cout << "Zip: " << p.zip << endl;

   // Add sufficent spacing between records
   if(settings != "") cout << endl;
}


//
// pre_order_traversal
// Traverse the tree starting at root and
// Then go to the left side and then right
// The result is the data is printed in order.
//
void pre_order_traversal( Tree<Person>* node, string settings ) {
   // Ensure node exists
   if( node == NULL ) return;

   // Print node's data
   print_data(node->get_data(), settings);

   // Recursively go to left side of tree
   if( node->get_left() != NULL ) pre_order_traversal(node->get_left(), settings);

   // Recursively go to right side of tree
   if( node->get_right() != NULL ) pre_order_traversal(node->get_right(), settings);
}

//
// in_order_traversal
// Traverse the tree on the left side
// Then go to the root then the right side.
// The result is the data is printed in order.
//
void in_order_traversal( Tree<Person>* node, string settings ) {
   // Ensure that node exists
   if( node == NULL ) return;

   // Recursively go to left side of tree
   if( node->get_left() != NULL ) in_order_traversal(node->get_left(), settings);

   // Print the node's data
   print_data(node->get_data(), settings);

   // Recursively go to right side of tree
   if( node->get_right() != NULL ) in_order_traversal(node->get_right(), settings);
}

//
// post_order_traversal
// Traverse the tree starting at root
// Then go to the left side then the right side.
//
void post_order_traversal( Tree<Person>* node, string settings ) {
   // Ensure that node exists
   if( node == NULL ) return;

   // Recursively go to left side of tree
   if( node->get_left() != NULL ) post_order_traversal(node->get_left(), settings);

   // Recursively go to right side of tree
   if( node->get_right() != NULL ) post_order_traversal(node->get_right(), settings);

   //Print the node's data
   print_data(node->get_data(), settings);
}

//
// breadth_first_traversal
// Traverse the tree starting at root
// Then go to the left side then the right side.
//
void breadth_first_traversal( Tree<Person>* node, string settings ) {
//    Ensure root node exists
   if (node->get_root() == NULL)  return;

   // Create an empty queue
   queue<Tree <Person>> q;

   // Enqueue root
   q.push(*node->get_root());

   // Continue to go through each node while queue is not empty
   while ( !q.empty() ) {
      // Get and print front of queue
      Tree<Person> node = q.front();
      print_data(node.get_data(), settings);

      q.pop(); // Remove the node from the queue

      // Enqueue left node
      if (node.get_left() != NULL) q.push(*node.get_left());

      // Enqueue right node
      if (node.get_right() != NULL) q.push(*node.get_right());
   }
}





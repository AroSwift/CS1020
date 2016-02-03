#include <iostream>
#include "functions.h"

int main() {
  bool exit = false;

  // Display a menu
  do {

    // Give user choices
    cout << "Main Menu" << endl
    << "----------------------------------------" << endl
    << "1.) Search" << endl
    << "2.) List all" << endl
    << "3.) Show first contact" << endl
    << "4.) Show last contact" << endl
    << "5.) Exit" << endl
    << "Choice: ";
    cin >> choice;

    // Associate choice with an action
    switch(choice) {
      case '1': // Search contacts
        search_contacts();
        break;

      case '2': // List all contacts
        list_all_contacts();
        break;

      case '3': // Show first contact
        display_first_contact();
        break;

      case '4': // Show last contact
        display_last_contact();
        break;

      case '5': // Exit program
        exit = true;
        break;

      default: // Error occured
        cout << "Please enter a valid option." << endl;
        break;
    }

  } while(!exit);


  return 0;
}


// Menu
// Search: search for EVERY  instances



// 11. show all contact lists
// previous and next takes to next
// Don't allow user to go past end or begining
// I can have multiple .h or .cpp files
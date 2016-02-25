#include <iostream>
using namepsace std;

int main() {
  bool tickets_available = true

  while(tickets_available) {
    sleep(SLEEP_TIME);
    // Then get tickets
    // Process tickets
  }

  return 0;
}


void Ticket::get_tickets() {
  ifstream input;

  // Read in file
  input.open(FILE_NAME);

  // When file could not be found
  if( input.fail() ) {
    cout << "Input file " << filename << " does not exist. \n";
    exit(1);

  // When file is empty
  } else if( input.peek() == EOF ) {
    cout << "Input file " << filename << " is empty. \n";
    exit(1);
  }

}

void Ticket::print_tickets() {

}
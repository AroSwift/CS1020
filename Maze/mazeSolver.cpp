//
// Name: Aaron Barlow
// Date: 2/21/2016
// Description: Read in a given file
// in order to attempt to solve a maze.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "mazeSolver.h"
using namespace std;


int main() {
  Stack s;

  int position_x, position_y;
  get_dimensions( position_x, position_y );

  // char maze[position_x][position_y];
  // load_maze( position_x, position_y, maze );

  return 0;
}


bool get_file_name( char filename[] ) {
  bool file_errors = false;
  ifstream input;

  cout << "Enter input file name: ";
  cin.getline( filename, MAX_FILE_LENGTH ); // Max file length on linux is 255

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

  // Close file
  input.close();

  return file_errors;
}

void get_dimensions( int& position_x, int& position_y ) {
  char filename[MAX_FILE_LENGTH];
  bool file_errors;
  ifstream input;

  do { // Find a file that exists
    file_errors = get_file_name( filename );
  } while( file_errors );

  input >> position_x;
  input >> position_y;

  if( !isdigit(position_x) || !isdigit(position_y) ) {
    cout << "The dimensions for the maze are invalid." << endl;
  }


}

// void load_maze( int position_x, int position_y, char maze[][position_y] ) {
//   char filename[MAX_FILE_LENGTH];
//   bool file_errors;
//   ifstream input;

//   do { // Find a file that exists
//     file_errors = get_file_name( filename );
//   } while( file_errors );

//   input.open( filename );


//   for( int row = 0; row < position_x; row++ ) {

//     for( int col = 0; col < position_y; col++ ) {

//       input >> maze[position_x][position_y];

//     }
//     // !input.eof()

//   }


//   // Close file
//   input.close();

// }


// void print_maze() {

// }

// bool is_maze_end( int position_x, int position_y ) {

// }


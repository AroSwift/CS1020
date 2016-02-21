//
// Name: Aaron Barlow
// Date: 2/21/2016
// Description: Read in a given file
// in order to attempt to solve a maze.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include "mazeSolver.h"
using namespace std;


int main() {
  ifstream input;
  Maze *m = new Maze();
  bool solved;

  // m->num_rows = 10;
  // cout << m->num_rows << endl;

  // cout << "Before get file" << endl;

  // // Open file
  // get_file( input );
  // // Get the dimensions of the maze
  // cout << "get dimensions" << endl;
  // get_dimensions( input, m );

  // cout << "dynamic" << endl;

  int num_rows = 10;
  int num_cols = 10;

  // dynamic allocation
  m->maze = new char*[num_rows];
  for(int i = 0; i < num_rows; ++i) m->maze[i] = new char[num_cols];

  // cout << "Load maze" << endl;

  // // Load the maze into a 2d demensional array
  // load_maze( input, m );

  // // Attempt to solve maze
  // // solved = solve_maze( maze );

  // if(solved) {
  //   // Print the maze if maze was solved
  //   // print_maze( maze );
  // } else {
  //   cout << "The maze can not be solved.";
  // }

  // // Delete dynamically allocated 2d dimensional array
  // // for(int row = 0; row < rows; ++row) delete [] maze[row];
  // // delete [] maze;

  // // Close the file
  // input.close();

  return 0;
}


void get_file( ifstream& input ) {
  bool file_errors;
  char filename[MAX_FILE_LENGTH];

  do { // Find a file that exists
    file_errors = false;

    cout << "Enter file name: ";
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

    // Reset buffer
    input.clear();

  } while( file_errors );

}

int get_dimensions( ifstream& input, Maze *m ) {
  bool file_errors;

  cout << "here?" << endl;

  input >> m->num_rows;
  input >> m->num_cols;

  cout << m->num_rows << "  " << m->num_cols << endl;

  // input.ignore();
  // if( !isdigit(rows) || !isdigit(cols) ) {
  //   cout << "The dimensions for the maze are invalid." << endl;
  //   exit(1);
  // }

}

// void doIt( char *maze, int cols, int row, int col );
// OR
// MAZE[ ( row * cols ) + col ]

void load_maze( ifstream& input, Maze *m ) {
  // Ignore the newline
  input.ignore(1, '\n');

  for( int row = 0; row < m->num_rows; row++ ) {

    input.getline( m->maze[row], m->num_cols );

    // cout << row << "  Char: \"" << maze[row] << "\"" << endl;

    // if( input.eof() ) cout << "Given dimensions do not map to the maze." << endl;

  }

}

bool solve_maze( Maze *m ) {
  Stack current_location, options_location;
  initStack(&current_location);
  initStack(&options_location);
  bool solved = false;

  // for( int row = START_ROW; row < rows; row++ ) {
  //   for( int col = START_COL; col < cols; col++ ) {

  // int current_row = START_ROW;
  // int current_col = START_COL;

  m->current_row = START_ROW;
  m->current_col = START_COL;

  m->maze[m->current_row][m->current_col] = '*';

  while(!solved) {

    // Maze adjacent_tiles[] = { p-> }

    m->get_down();
    m->get_right();
    m->get_left();
    m->get_up();

    // int num_options = get_num_options( down,right, left, up );

    // When more than one option, push onto the options stack
    // if(num_options > 1) {
    //   Maze *p;
    //   p->current_row = current_row;
    //   p->current_col = current_col;
    //   push(&options_location, p);
    // }

    // isEmpty(options_location);

    // print_maze( maze, rows, cols );

  }

      // push( &current_location, maze[row][col], stack... );
  //   }
  // }

  // State of maze being solved
  return solved;
}

int Maze::get_num_options() {
  // int num_options;

  // if( is_path(down) ) num_options++;
  // if( is_path(right) ) num_options++;
  // if( is_path(left) ) num_options++;
  // if( is_path(up) ) num_options++;

  // return num_options;
}

char Maze::get_down() {
  // if(row < rows) maze[row+1][col];
}

char Maze::get_right() {
  // if(col < cols) maze[row][col+1];
}

char Maze::get_left() {
  // if(col != 0) maze[row][col-1];
}

char Maze::get_up() {
  // if(row != 0) maze[row-1][col];
}

bool Maze::is_wall() {
  // for( int i = 0; WALL[i] != '\0'; i++ ) {
  //   if(position == WALL[i]) {
  //     return true;
  //   }
  // }

  // // Otherwise, char is not wall
  // return false;
}

bool Maze::is_path() {
  // return position == PATH ? true : false;
}

bool Maze::is_exit() {
  // if( is_path(position) ) {
  //   // if( row == max_rows || col == max_rows ) {
  //   //   return true;
  //   // }
  //   return true;
  // }
  // return false;
}

void print_maze( Maze *m) {
  // for( int row = 0; row < rows; row++ ) cout << maze[row] << endl;
}



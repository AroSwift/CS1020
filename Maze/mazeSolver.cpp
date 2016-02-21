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

  // Open file
  get_file( input );
  // Get the dimensions of the maze
  get_dimensions( input, m );

  // dynamic allocation
  m->maze = new char*[m->num_rows];
  for(int i = 0; i < m->num_rows; ++i) m->maze[i] = new char[m->num_cols];

  // Load the maze into a 2d demensional array
  load_maze( input, m );

  // Attempt to solve maze
  bool solved = solve_maze( m );

  if(solved) {
    print_maze( m );
  } else {
    cout << "The maze can not be solved." << endl;
  }

  // Delete dynamically allocated 2d dimensional array
  for(int row = 0; row < m->num_rows; ++row) delete [] m->maze[row];
  delete [] m->maze;

  // // Close the file
  input.close();

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

  input >> m->num_rows;
  input >> m->num_cols;

  // cout << m->num_rows << "  " << m->num_cols << endl;

  // input.ignore();
  // if( !isdigit(rows) || !isdigit(cols) ) {
  //   cout << "The dimensions for the maze are invalid." << endl;
  //   exit(1);
  // }

}

void load_maze( ifstream& input, Maze *m ) {
  // Ignore the newline
  input.ignore(1, '\n');

  for( int row = 0; row < m->num_rows; row++ ) {

    input.getline( m->maze[row], m->num_cols );

    // cout << row << "  Char: \"" << m->maze[row] << "\"" << endl;

    // if( input.eof() ) cout << "Given dimensions do not map to the maze." << endl;

  }

  // Ensure maze is valid
  // validate_maze(m);

}

// void validate_maze(Maze *m) {
//   bool error = false;

//   for( int row = 0; row < m->num_rows; row++ ) {
//     for( int col = 0; col < m->num_cols; col++ ) {

//       for( int i = 0; WALL[i] != '\0'; i++ ) {
//         if(m->maze[row][col] == WALL[i]) error = true;
//       }

//       if(m->maze[row][col] != PATH) error = true;

//     }
//   }

//   if(error) {
//     cout << "The maze is invalid." << endl;
//     exit(1);
//   }
// }

bool solve_maze( Maze *m ) {
  initStack(&m->current_location);
  initStack(&m->options_location);
  bool solved = false;

  // for( int row = START_ROW; row < rows; row++ ) {
  //   for( int col = START_COL; col < cols; col++ ) {

  m->current_row = START_ROW;
  m->current_col = START_COL;

  m->maze[m->current_row][m->current_col] = '*';

  while(!solved) {
    int num_options = 0;

    // Maze adjacent_tiles[] = { p-> }

    // When down is possible
    if( m->current_row < m->num_rows ) {
      m->get_down();
      num_options++;

    // When right is possible
    } else if( m->current_col < m->num_cols ) {
      m->get_right();
      num_options++;

    // When left is possible
    } else if( m->current_col != 0 ) {
      m->get_left();
      num_options++;

    // When up is possible
    } else if( m->current_row != 0 ) {
      m->get_up();
      num_options++;
    }

    if( num_options > 1 ) {
      // When more than one option, push onto the options stack
      push(&m->options_location, m);

    // When no options, pop back if possible
    } else {
      if( isEmpty(&m->options_location) ) {
        // Impossible to solve
        solved = false;
        break;
      } else {
        pop( &m->options_location );
      }
    }


    if( m->is_exit() ) solved = true;



    print_maze( m );

  }

  // State of maze resolution
  return solved;
}

// bool Maze::down_possible() {
//   return current_row < num_rows ? true : false;
// }

// bool Maze::right_possible() {
//   return current_col < num_cols ? true : false;
// }
// bool Maze::left_possible() {
//   return current_col != 0 ? true : false;
// }
// bool Maze::up_possible() {
//   return current_row != 0 ? true : false;
// }

char Maze::get_down() {
 return maze[current_row+1][current_col];
}

char Maze::get_right() {
  return maze[current_row][current_col+1];
}

char Maze::get_left() {
 return maze[current_row][current_col-1];
}

char Maze::get_up() {
 return maze[current_row-1][current_col];
}

bool Maze::is_wall() {
  for( int i = 0; WALL[i] != '\0'; i++ ) {
    if(maze[current_row][current_col] == WALL[i]) {
      return true;
    }
  }

  // Otherwise, char is not wall
  return false;
}

bool Maze::is_path() {
  return maze[current_row][current_col] == PATH ? true : false;
}

bool Maze::is_exit() {
  if( is_path() ) {
    if( current_row == num_rows || current_col == num_cols ) {
      return true;
    }
  }

  // Otherwise, is not maze exit
  return false;
}

void print_maze( Maze *m) {
  for( int row = 0; row < m->num_rows; row++ ) cout << m->maze[row] << endl;
}


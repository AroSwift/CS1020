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
  Stack current_location, options_location;
  initStack(&current_location);
  initStack(&options_location);
  bool solved = false;

  m->cords.row = START_ROW;
  m->cords.col = START_COL;
  push(&current_location, &m->cords);

  m->maze[m->cords.row][m->cords.col] = '*';

  while(!solved) {
    int num_options = 0;

    // Maze adjacent_tiles[] = { p-> }

    // When down is possible
    if( m->down_possible() ) {
      m->cords.row++;
      push(&current_location, &m->cords);
      num_options++;
    }

    // When right is possible
    if( m->right_possible() ) {
      m->cords.col++;
      push(&current_location, &m->cords);
      num_options++;
    }

    // When left is possible
    if( m->left_possible() ) {
      m->cords.col--;
      push(&current_location, &m->cords);
      num_options++;
    }

    // When up is possible
    if( m->up_possible() ) {
      m->cords.row--;
      push(&current_location, &m->cords);
      num_options++;
    }

    if( num_options > 1 ) {
      // When more than one option, push onto the options stack
      push(&options_location, &m->cords);

    // When no options, pop back if possible
    } else {
      if( isEmpty(&options_location) ) {
        // Impossible to solve
        solved = false;
        break;
      } else {
        Cords *new_cords = (Cords*)pop( &options_location );
        m->cords = *new_cords;
      }
    }


    if( m->is_exit() ) solved = true;


    print_maze( m );

  }

  // State of maze resolution
  return solved;
}

bool Maze::down_possible() {
  if( cords.row < num_rows && is_path(get_down()) ) return true;
  // Otherwise, down is not possible
  return false;
}

bool Maze::right_possible() {
  if( cords.col < num_cols && is_path(get_right()) ) return true;
  // Otherwise, right is not possible
  return false;
}
bool Maze::left_possible() {
  if( cords.col != 0 && is_path(get_left()) ) return true;
  // Otherwise, left is not possible
  return false;
}

bool Maze::up_possible() {
  if( cords.row != 0 && is_path(get_up()) ) return true;
  // Otherwise, down is not possible
  return false;
}

char Maze::get_down() {
 return maze[cords.row+1][cords.col];
}

char Maze::get_right() {
  return maze[cords.row][cords.col+1];
}

char Maze::get_left() {
 return maze[cords.row][cords.col-1];
}

char Maze::get_up() {
 return maze[cords.row-1][cords.col];
}

bool is_wall( char c ) {
  for( int i = 0; WALL[i] != '\0'; i++ ) {
    if(c == WALL[i]) {
      return true;
    }
  }

  // Otherwise, char is not wall
  return false;
}

bool is_path( char c ) {
  return c == PATH ? true : false;
}

bool Maze::is_exit() {
  if( is_path(maze[cords.row][cords.col]) ) {
    if( cords.row == num_rows || cords.col == num_cols ) {
      return true;
    }
  }

  // Otherwise, is not maze exit
  return false;
}

// void Maze::set_position( Stack *s ) {
//   push(&s, &cords);
// }

void print_maze( Maze *m) {
  for( int row = 0; row < m->num_rows; row++ ) cout << m->maze[row] << endl;
}


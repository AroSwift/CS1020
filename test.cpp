#include <iostream>
using namespace std;

struct Person {
 string name;
};

int main() {
  Person *p = new Person();

  for( int i = 0; i < 3; i++ ) {
    cout << "Enter name: ";
    cin >> p->[i]name;
  }

  for( int i = 0; i < 3; i++ ) {
    cout << "Name: " << p->[i]name << endl;
  }

  return 0;
}
#include <iostream>
#include "stack.h"
using namespace std;

int main() {
   stack<string> s;
   s.push("David");
   s.push("Pam");
   s.push("Danny");
   cout << s.pop() << endl;
   cout << s.pop() << endl;
   cout << s.pop() << endl;
}



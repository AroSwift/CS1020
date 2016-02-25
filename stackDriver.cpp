//
// stackDriver.cpp
// Written by: Dr. Brown
// 02/24/2016
//
#include <iostream>
#include "stack.h"
using namespace std;

int main() {
 Stack s;
 s.push((void *)"David");
 s.push((void *)"Danny");
 s.push((void *)"Mike");
 cout << (char *)s.pop() << endl;
 cout << (char *)s.pop() << endl;
 cout << (char *)s.pop() << endl;
}
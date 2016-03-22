#include <iostream>
using namespace std;

void printNum(int x);
void getAndPrint(void (*pNum)(int));

int main() {
 getAndPrint(&printNum);
}

void printNum(int x) {
 cout << "num: " << x << endl;
}

void getAndPrint(void (*pNum)(int) ) {
 cout << "Enter a number: ";
 int num;
 cin >> num;
 pNum(num);
}
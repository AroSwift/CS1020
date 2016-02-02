#include <iostream>
using namespace std;

struct Person {
 string name;
 Person *next;
};

void insert(Person **first, string name);
void traverse(Person *first);

int main() {
 string names[] = {"David", "Pam", "Karen"};
 Person *first = (Person *)0;

 for(int i = 0; i < 3; i++) {
    insert(&first, names[i]);
 }
 traverse(first);
}

void insert(Person **first, string name) {
 Person *p = new Person();
 p->name = name;
 p->next = (Person *)0;
 if (*first != (Person *)0)
    p->next = *first;
 *first = p;
}

void traverse(Person *first) {
 while(first != (Person *)0) {
    cout << first->name << endl;
    first = (Person *)first->next;
 }
}
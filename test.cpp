#include <iostream>
#include <vector>
using namespace std;

struct Person {
 string first, last;
};

void sortStrings(vector<string>& v);
void sortPeople(vector<Person>& v);
void printStrings(vector<string> v);
void printPeople(vector<Person> v);
bool comparePeople(Person p1, Person p2);

int main() {
 vector<string> strVect;
 string strArray[] = {"test", "unknown", "david", "brown"};
 strVect.assign(&strArray[0], &strArray[0] + 4);

 vector<Person> personVect;
 Person personArray[] = {{"David","Brown"}, {"John","Smith"}, {"Billy","Watson"}, {"Randall", "Jones"}};
 personVect.assign(&personArray[0], &personArray[0] + 4);

 sortStrings(strVect);
 printStrings(strVect);

 sortPeople(personVect, comparePeople);
 printPeople(personVect);
}

void printStrings(vector<string> v) {
 cout << endl << "Strings: " << endl;
 for(int i = 0; i < v.size(); i++)
 cout << v[i] << endl;
}

void printPeople(vector<Person> v) {
 cout << endl << "People: " << endl;
 for(int i = 0; i < v.size(); i++)
 cout << v[i].first << " " << v[i].last << endl;
}

void sortStrings(vector<string>& v) {
 for(int i = 0; i < v.size() - 1; i++)
 for(int j = i+1; j < v.size(); j++)
 if(v[j] < v[i]) {
 string temp = v[i];
 v[i] = v[j];
 v[j] = temp;
 }
}

void sortPeople(vector<Person>& v, bool (*comparePeople)(Person, Person)) {
 for(int i = 0; i < v.size() - 1; i++)
 for(int j = i+1; j < v.size(); j++)
 if( comparePeople(v[j], v[i]) ) {
 Person temp = v[i];
 v[i] = v[j];
 v[j] = temp;
 }
}

bool comparePeople(vector<Person>& p1, vector<Person>& p2) {
  return (p1.last < p2.last) || ((p1.last == p2.last) && (p1.first < p2.first));
}



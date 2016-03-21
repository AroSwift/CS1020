#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class stack {
      vector<T> v;
   public:
      void push(T s);
      T pop();
      bool isEmpty();
};

template<class T>
void stack<T>::push(T s) {
   v.push_back(s);
}

template <class T>
T stack<T>::pop() {
   T s = v.back();
   v.pop_back();
   return(s);
}

template <class T>
bool stack<T>::isEmpty() {
   return(v.size() == 0);
}

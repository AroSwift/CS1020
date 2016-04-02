const int MAX_DATA = 100;

temtemplate <class T>
class STack {
  T data[MAX_DATA];
  int top;
public:
  Stack();
  void push(T d);
  T pop();
  bool is_empty();
};

Stack::Stack() {
  top = -1;
}

template<class T>
void Stack::push(T d) {
  if( top == MAX_DATA ) return;
  data[++top] = d;
}

template<class T>
T Stack::pop() {
  if( is_empty() ) return;
  T temp_data = data[top--];
  delete data;
  return temp_data;
}

template<class T>
bool Stack::is_empty() {
  return(top == -1) ? true : false;
}
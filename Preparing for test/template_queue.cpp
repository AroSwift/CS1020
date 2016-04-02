template<class T>
class Queue {
  Queue *next, *prev, *front, *back;
  T data;
public:
  Stack() {};
  Stack(T d);
  void insert_back(T d);
  T pop_back();
  bool is_empty();
};


Stack::Stack(T d) {
  data = d;
  next = prev = NULL;
}

void Queue::insert_back(T d) {
  Queue *new_data = new Queue(d);
  if( front == NULL && back == NULL ) {
    front = back = new_data;
  } else {
    back->prev = new_data;
    new_data->next = back;
    back = new_data;
  }
}

T Queue::pop_front() {
  if( is_empty() ) return;

  Queue *new_front = front->prev;
  T temp_data = front->data;
  front->prev = front->next = NULL;
  delete front;
  front = new_front;
  return temp_data;
}

bool Queue::is_empty() {
  return (front == NULL && back == NULL) ? true : false;
}


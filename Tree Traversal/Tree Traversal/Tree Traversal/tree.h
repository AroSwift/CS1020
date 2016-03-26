#pragma once
using namespace std;

template<class T>
class Tree {
   T data;
   Tree* root;
   Tree* left;
   Tree* right;
public:
   Tree();
//   ~Tree();
   void insert(T data, bool (*cp)(T, T));
   Tree<T>* insert( Tree* node, T data, bool (*cp)(T, T));
   void print_data(T data);
   void in_order_traversal();
   void pre_order_traversal();
   void post_order_traversal();
   void breadth_first_traversal();
   void in_order_traversal( Tree* node );
   void pre_order_traversal( Tree* node );
   void post_order_traversal( Tree* node );
   void breadth_first_traversal( Tree* node );
};


template<class T>
Tree<T>::Tree() {
   root = NULL;
   left = NULL;
   right = NULL;
//   data = NULL;
}

//template<class T>
//Tree<T>::~Tree() {
//    return root;
//}

template <class T>
void print_data(T data) {
   cout << data << endl;
}

template<class T>
void Tree<T>::insert(T data, bool (*cp)(T, T)) {
   insert(root, data, cp);
}

template<class T>
Tree<T>* Tree<T>::insert( Tree* node, T data, bool (*cp)(T, T)) {
   if( root == NULL ) {
      Tree* node = new Tree();
      node->data = data;
      node->left = node->right = NULL;
   } else if( cp(data, node->data) ) {
      node->left = insert(node->left, data, cp);
      return node->left;
   } else {
      node->right = insert(node->right, data, cp);
      return node->right;
   }
   return NULL;
}

template<class T>
void Tree<T>::pre_order_traversal() {
   pre_order_traversal(root);
}

template<class T>
void Tree<T>::in_order_traversal() {
   in_order_traversal(root);
}

template<class T>
void Tree<T>::post_order_traversal() {
   post_order_traversal(root);
}

template<class T>
void Tree<T>::breadth_first_traversal() {
   breadth_first_traversal(root);
}

template<class T>
void Tree<T>::pre_order_traversal( Tree* node ) {
   if( root == NULL ) return;

//   print_data(data);

   if( node->left != NULL ) {
      pre_order_traversal( node->left);
   }

   if( node->right != NULL ) {
      pre_order_traversal( node->right );
   }
}

template<class T>
void Tree<T>::in_order_traversal( Tree* node ) {
   if( root == NULL ) return;

   if( node->left != NULL ) {
      in_order_traversal( node->left );
   }

//   print_data(data);

   if( node->right != NULL ) {
      in_order_traversal( node->right );
   }
}

template<class T>
void Tree<T>::post_order_traversal( Tree* node ) {
   if( root == NULL ) return;

   if( node->left != NULL ) {
      post_order_traversal( node->left );
   }

   if( node->right != NULL ) {
      post_order_traversal( node->right );
   }

//   print_data(data);
}


template<class T>
void Tree<T>::breadth_first_traversal( Tree* node) {

}


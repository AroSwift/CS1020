#pragma once
using namespace std;

template<class T>
class Tree {
   T data;
   Tree *root;
   Tree *left;
   Tree *right;
public:
   Tree();
//   ~Tree();
   void insert(T data);
   void insert( Tree* node, T data);
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
}

//template<class T>
//Tree<T>::~Tree() {
//    return root;
//}

template <typename T>
void print_data(T data) {
   cout << data << endl;
}

template<class T>
void Tree<T>::print_data( T data ) {
   cout << data;
}

template<class T>
void Tree<T>::insert(T data) {
   Tree* tree = new Tree();
   tree->data = data;
   tree->left = tree->right = NULL;

   if( root == NULL ) tree->root = tree;


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
void Tree<T>::pre_order_traversal( Tree* node ) {
   if( root == NULL ) return;

    print_data(data);

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

   print_data(data);

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

   print_data(data);
}


template<class T>
void Tree<T>::breadth_first_traversal( Tree* node) {

}


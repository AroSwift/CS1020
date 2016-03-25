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
   T left_node();
   T right_node();
   void insert(T data);
   void print_data(T data);
   void in_order_traversal( Tree* node );
   void pre_order_traversal( Tree* node );
   void post_order_traversal( Tree* node );
   void breadth_first_traversal( Tree* node);
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
void Tree<T>::insert(T data) {
   Tree* tree = new Tree();
   tree->data = data;
   tree->left = NULL;
   tree->right = NULL;

   if( root == NULL ) tree->root = tree;


}

template<class T>
void Tree<T>::pre_order_traversal( Tree* root ) {
   if( root == NULL ) return;

    print_data(data);

   if( root->left != NULL ) {
      pre_order_traversal( root->left);
   }

   if( root->right != NULL ) {
      pre_order_traversal( root->right );
   }
}

template<class T>
void Tree<T>::in_order_traversal( Tree* root ) {
   if( root == NULL ) return;

   if( root->left != NULL ) {
      in_order_traversal( root->left );
   }

   print_data(data);

   if( root->right != NULL ) {
      in_order_traversal( root->right );
   }
}

template<class T>
void Tree<T>::post_order_traversal( Tree* root ) {
   if( root == NULL ) return;

   if( root->left != NULL ) {
      post_order_traversal( root->left );
   }

   if( root->right != NULL ) {
      post_order_traversal( root->right );
   }

   print_data(data);
}


template<class T>
void Tree<T>::breadth_first_traversal( Tree* node) {

}

template<class T>
void Tree<T>::print_data( T data ) {
   cout << data;
}






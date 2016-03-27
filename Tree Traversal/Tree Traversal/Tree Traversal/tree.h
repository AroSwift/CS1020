#pragma once
using namespace std;

template<class T>
class Tree {
public:
   Tree();
   ~Tree();
   void insert(T data, bool (*cp)(T, T));
   void print_data(T data);
   void in_order_traversal();
   void pre_order_traversal();
   void post_order_traversal();
   void breadth_first_traversal();
//   void search_data(T data, bool (*cp)(T, T))
private:
   T data;
   Tree* root;
   Tree* left;
   Tree* right;
   void in_order_traversal( Tree* node );
   void pre_order_traversal( Tree* node );
   void post_order_traversal( Tree* node );
   void breadth_first_traversal( Tree* node );
//   void insert( Tree* node, T data, bool (*cp)(T, T));
   void remove(Tree* node);
};


template<class T>
Tree<T>::Tree() {
   left = NULL;
   right = NULL;
}

template<class T>
Tree<T>::~Tree() {
   remove(root);
}

template<class T>
void Tree<T>::remove(Tree* node) {
   if(node != NULL) {
      remove(node->left);
      remove(node->right);
      delete node;
//      node = NULL;
   }
}

template <class T>
void Tree<T>::print_data(T data) {
   cout << data << endl;
}

//template<class T>
//void Tree<T>::insert(T data, bool (*cp)(T, T)) {
//   insert(root, data, cp);
//}

template<class T>
void Tree<T>::insert( T data, bool (*cp)(T, T)) {
   if( root == NULL ) {
      root = new Tree<T>;
      root->data = data;
      root->left = root->right = NULL;
//      if( root == NULL ) root = new_node;
   } else {
      Tree *current = root;
      bool inserted = false;
      // search for the place to insert the new value
      do {
         if ( current->data < data ) {
            // if the current node already has left child
            // so we concern it further
            if ( NULL != current->left ) {
               current = current->left;
               // if the current node has no left child
               // so we create it with the new value
            } else {
               current->left = new Tree<T>;
               current->left->data = data;
               inserted = true;
            }
         } else {
            // similarly for the value that should be inserted into
            // right subtree
            if ( NULL != current->right ) {
               current = current->right;
            } else {
               current->right = new Tree<T>;
               current->right->data = data;
               inserted = true;
            }
         }
      } while( !inserted );
   }
      
}

//template<class T>
//T data Tree<T>::search_data(T data, bool (*cp)(T, T)) {
//   while(  ) {
//   if( cp( data, node->data ) ) {
//      //      Tree* node = new Tree();
//      Tree<T>* node = new Tree<T>;
//      node->data = data;
//      node->left = node->right = NULL;
//      if( root == NULL ) root = node;
//   } else if( cp(data, node->data) ) {
//      node->left = insert(node->left, data, cp);
//   } else {
//      node->right = insert(node->right, data, cp);
//   }
//      
//      
//      
//   return node;
//}

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
   if( node == NULL ) return;

   print_data(node->data);

   if( node->left != NULL ) {
      pre_order_traversal(node->left);
   }

   if( node->right != NULL ) {
      pre_order_traversal(node->right);
   }
}

template<class T>
void Tree<T>::in_order_traversal( Tree* node ) {
   if( node == NULL ) return;

   if( node->left != NULL ) {
      in_order_traversal(node->left);
   }

   print_data(node->data);

   if( node->right != NULL ) {
      in_order_traversal(node->right);
   }
}

template<class T>
void Tree<T>::post_order_traversal( Tree* node ) {
   if( node == NULL ) return;

   if( node->left != NULL ) {
      post_order_traversal(node->left);
   }

   if( node->right != NULL ) {
      post_order_traversal(node->right);
   }

   print_data(node->data);
}


template<class T>
void Tree<T>::breadth_first_traversal( Tree* node) {
   print_data(node->data);
}


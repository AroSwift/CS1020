#pragma once
#include <queue>
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
//   T find_data(T data, bool (*less_greater_cp)(T, T), bool (*equal_cp)(T, T));
   void search(T data, bool (*cp)( T, T ));
private:
   T data;
   Tree* root;
   Tree* left;
   Tree* right;
   void in_order_traversal( Tree* node );
   void pre_order_traversal( Tree* node );
   void post_order_traversal( Tree* node );
   void search(Tree* node, T d, bool (*cp)( T, T ), int num_searches);
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
   if(node == root) return;
   if(node->left != NULL) remove(node->left);
   if(node->right != NULL)remove(node->right);
   delete node;
}

template <class T>
void Tree<T>::print_data(T data) {
   cout << data << endl;
}

template<class T>
void Tree<T>::insert( T data, bool (*cp)(T, T)) {
   if( root == NULL ) {
      root = new Tree<T>;
      root->data = data;
      root->left = root->right = NULL;
   } else {
      Tree *current = root;
      bool inserted = false;
      // search for the place to insert the new value
      do {
         if ( cp(current->data, data) ) {
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
//T Tree<T>::find_data(T data, bool (*less_greater_cp)(T, T), bool (*equal_cp)(T, T)) {
//   if( root == NULL ) return boost::none;
//   
//   Tree<T> current = root;
//   bool data_found = false, done_searching = false;
//   while( !data_found && !done_searching ) {
//      if( equal_cp( data, current->data ) ) {
//         data_found = true;
//      } else if( less_greater_cp( data, current->data ) ) {
//         current = current->left;
//      } else {
//         current = current->right;
//      }
//      
//   }
//   
//   return (data_found) ? current->data : NULL;
//}

template<class T>
void Tree<T>::search(T data, bool (*cp)( T, T )) {
   search( root, data, cp, 1 );
}

template<class T>
void Tree<T>::search(Tree* node, T d, bool (*cp)( T, T ), int num_searches) {
   if(node == NULL) return;
   
//   if( node->data == d ) {
   if( cp(node->data, d) ) {
   cout << num_searches << " nodes were traversed to find the data." << endl;
      print_data(d);
      return;
   }
   
   if( node->left != NULL ) node->left->search( node->left, d, cp, num_searches++ );
   if( node->right != NULL ) node->right->search( node->right, d, cp, num_searches++ );
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
   if( node == NULL ) return;
   
   print_data(node->data);
   
   if( node->left != NULL ) pre_order_traversal(node->left);
   if( node->right != NULL ) pre_order_traversal(node->right);
}

//
// in_order_traversal
// Traverse the tree on the left side
// Then go to the root then the right side.
// The result is the data is printed in order.
//
template<class T>
void Tree<T>::in_order_traversal( Tree* node ) {
   // Ensure that node exists
   if( node == NULL ) return;
   
   // Recursively go to left side of tree
   if( node->left != NULL ) in_order_traversal(node->left);
   
   // Print the node's data
   print_data(node->data);
   
   // Recursively go to right side of tree
   if( node->right != NULL ) in_order_traversal(node->right);
}

//
// post_order_traversal
// Traverse the tree starting at root
// Then go to the left side then the right side.
//
template<class T>
void Tree<T>::post_order_traversal( Tree* node ) {
   // Ensure that node exists
   if( node == NULL ) return;
   
   // Recursively go to left side of tree
   if( node->left != NULL ) post_order_traversal(node->left);
   
   // Recursively go to right side of tree
   if( node->right != NULL ) post_order_traversal(node->right);
   
   //Print the node's data
   print_data(node->data);
}

//
// breadth_first_traversal
// Traverse the tree starting at root
// Then go to the left side then the right side.
//
template<class T>
void Tree<T>::breadth_first_traversal() {
   if (root == NULL)  return;
   
   // Create an empty queue
   queue<Tree> q;
   
   // Enqueue root
   q.push(*root);
   
   // Continue to go through each
   while ( !q.empty() ) {
      // Get and print front of queue
      Tree<T> node = q.front();
      print_data(node.data);
      // Remove the node from the queue
      q.pop();
      
      // Enqueue left node
      if (node.left != NULL) q.push(*node.left);
      
      // Enqueue right node
      if (node.right != NULL) q.push(*node.right);
   }
}



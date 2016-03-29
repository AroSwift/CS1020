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
   void search(T d, bool (*eq)( T, T ));
private:
   T data;
   Tree* root;
   Tree* left;
   Tree* right;
   void in_order_traversal( Tree* node );
   void pre_order_traversal( Tree* node );
   void post_order_traversal( Tree* node );
   void search(Tree* node, T d, bool (*eq)( T, T ), int num_searches);
   void remove(Tree* node);
};


//
// Constructor for Tree
// Sets the left and right node to nothing
//
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

//
// print_data
// Prints the given template data.
// Note: this must be overwritten by
// a custom cout operator function.
//
template <class T>
void Tree<T>::print_data(T data) {
   cout << data << endl;
}

//
// insert
// Given a templated data and a function pointer for the comparison
// of the data, set the first inserted data equal to root.
// If the data is not root, then find it's order by comparing data with
// the function pointer and place it in the location in which it is
// alphebetically ordered with nodes.
//
template<class T>
void Tree<T>::insert( T data, bool (*cp)(T, T)) {
   // When the element is the first in the tree
   if( root == NULL ) {
      // Create a new tree and set it to root
      root = new Tree<T>;
      root->data = data;
      root->left = root->right = NULL;
   } else { // Not the first element in the tree
      Tree *current = root;
      bool inserted = false;
      
      // Search the tree to identify the alphebetically correct location to place the data
      do {
         // Use the function pointer to compare the current node's data against the new data
         if ( cp(current->data, data) ) {
            // When the current tree node does not exist
            if ( current->left == NULL ) {
               // Create a new node with the data
               current->left = new Tree<T>;
               current->left->data = data;
               inserted = true;
            } else { // The left node already exists
               current = current->left;
            }
         } else {
            // When the curent node does not exist
            if ( current->right == NULL ) {
               // Create a new tree node with the data
               current->right = new Tree<T>;
               current->right->data = data;
               inserted = true;
            } else { // The right node already exists
               current = current->right;
            }
         }
      // Continue to search the tree until the appropriate
      // position is identified and then the tree node is inserted
      } while( !inserted );
   }
   
}


template<class T>
void Tree<T>::search(T d, bool (*eq)( T, T )) {
   search( root, d, eq, 1 );
}

template<class T>
void Tree<T>::search(Tree* node, T d, bool (*eq)( T, T ), int num_searches) {
   // Ensure node exists
   if(node == NULL) return;
   
   // Determine if node's data is equal to given data using function pointer
   if( eq(node->data, d) ) {
      // Print the data and number of nodes traversed to find the data
      cout << num_searches << " nodes were traversed to find the data." << endl;
      print_data(d);
   } else { // Node's data is not equal to the given data
      if( node->left != NULL ) node->left->search( node->left, d, eq, num_searches++ );
      if( node->right != NULL ) node->right->search( node->right, d, eq, num_searches++ );
   }
}

//
// pre_order_traversal
// Call the private method pre_order_traversal
// and set the base case to root.
//
template<class T>
void Tree<T>::pre_order_traversal() {
   pre_order_traversal(root);
}

//
// in_order_traversal
// Call the private method in_order_traversal
// and set the base case to root.
//
template<class T>
void Tree<T>::in_order_traversal() {
   in_order_traversal(root);
}

//
// post_order_traversal
// Call the private method post_order_traversal
// and set the base case to root.
//
template<class T>
void Tree<T>::post_order_traversal() {
   post_order_traversal(root);
}

//
// pre_order_traversal
// Traverse the tree starting at root and
// Then go to the left side and then right
// The result is the data is printed in order.
//
template<class T>
void Tree<T>::pre_order_traversal( Tree* node ) {
   // Ensure node exists
   if( node == NULL ) return;
   
   // Print node's data
   print_data(node->data);
   
   // Recursively go to left side of tree
   if( node->left != NULL ) pre_order_traversal(node->left);
   
   // Recursively go to right side of tree
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
   // Ensure root node exists
   if (root == NULL)  return;
   
   // Create an empty queue
   queue<Tree> q;
   
   // Enqueue root
   q.push(*root);
   
   // Continue to go through each node while queue is not empty
   while ( !q.empty() ) {
      // Get and print front of queue
      Tree<T> node = q.front();
      print_data(node.data);
      
      q.pop(); // Remove the node from the queue
      
      // Enqueue left node
      if (node.left != NULL) q.push(*node.left);
      
      // Enqueue right node
      if (node.right != NULL) q.push(*node.right);
   }
}



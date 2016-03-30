#pragma once
using namespace std;

template<class T>
class Tree {
public:
   Tree();
   ~Tree();
   void insert(T data, bool (*cp)(T, T));
   Tree<T>* get_root();
   Tree<T>* get_left();
   Tree<T>* get_right();
   T get_data();
   T* search(Tree* node, T d, bool (*eq)( T, T ), int num_searches);
private:
   T data;
   Tree* root;
   Tree* left;
   Tree* right;
   void remove(Tree* node);
};

template<class T>
Tree<T>* Tree<T>::get_root() {
   return root;
}

template<class T>
Tree<T>* Tree<T>::get_left() {
   return left;
}
template<class T>
Tree<T>* Tree<T>::get_right() {
   return right;
}

template<class T>
T Tree<T>::get_data() {
   return data;
}


//
// Constructor for Tree
// Sets the left and right node to nothing
//
template<class T>
Tree<T>::Tree() {
   left = right = NULL;
}

//
// Destructor
// Call the remove method to remove all nodes attached to root and including root
//
template<class T>
Tree<T>::~Tree() {
   remove(root);
}

//
// remove
// Recursively call remove on node to delete the nodes
// from left to right.
//
template<class T>
void Tree<T>::remove(Tree* node) {
   // Ensure the current node exists
   if(node == NULL) return;
   if(node->left != NULL) remove(node->left);
   if(node->right != NULL)remove(node->right);
   // Deallocate node
   delete node;
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

//
// search
// Searches through the tree until the given data matches
// the node's data. If the data is never found in the tree
// Then inform the user that the data was not found.
//
template<class T>
T* Tree<T>::search(Tree* node, T d, bool (*eq)( T, T ), int num_searches) {
   // Ensure node exists
   if(node == NULL) return NULL;
   
   // Determine if node's data is equal to given data using function pointer
   if( eq(node->data, d) ) {
      // Print the data and number of nodes traversed to find the data
      cout << num_searches << " nodes were traversed to find the data." << endl;
//      print_data(node->data);
      return &node->data;
   } else { // Node's data is not equal to the given data
      T* outcome = NULL;
      if( node->left != NULL ) {
         outcome = search( node->left, d, eq, num_searches++ );
         if(outcome != NULL) return outcome;
      }
      if( node->right != NULL ) {
         outcome = search( node->right, d, eq, num_searches++ );
         if(outcome != NULL) return outcome;
      }
      return outcome;
   }
}


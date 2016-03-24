#pragma once
using namespace std;

template<class T>
class Tree {
    T data;
    Tree *root;
    Tree *left;
    Tree *right;
public:
//    Tree();
//    ~Tree();
    T get_root();
    T left_node();
    T right_node();
    void print_data(T data);
    void in_order_traversal( Tree* node );
    void pre_order_traversal( Tree* node );
    void post_order_traversal( Tree* node );
    void breadth_first_traversal( Tree* node);
};

//
//template<class T>
//T Tree<T>::Tree() {
//    
//}


//template<class T>
//T Tree<T>::get_root() {
//    return root;
//}

template<class T>
T Tree<T>::left_node() {
    return left;
}

template<class T>
T Tree<T>::right_node() {
    return right;
}


template <typename T>
void print_data(T data) {
    cout << data << endl;
}


template<class T>
void Tree<T>::pre_order_traversal( Tree* node ) {
//    print_person_data();
    if( node->left_node() != NULL ) {
        pre_order_traversal( node->left_node() );
    }

    if( node->right_node() != NULL ) {
        pre_order_traversal( node->right_node() );
    }
}

template<class T>
void Tree<T>::in_order_traversal( Tree* node ) {
    if( node->left_node() != NULL ) {
        in_order_traversal( node->left_node() );
    }
    
    // print data
    
    if( node->right_node() != NULL ) {
        in_order_traversal( node->right_node() );
    }
}

template<class T>
void Tree<T>::post_order_traversal( Tree* node ) {
    if( node->left_node() != NULL ) {
        post_order_traversal( node->left_node() );
    }
    
    if( node->right_node() != NULL ) {
        post_order_traversal( node->right_node() );
    }
    // print data
}

template<class T>
void Tree<T>::breadth_first_traversal( Tree* node) {
    
}







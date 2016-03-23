#pragma once

class Node {
    Node* left;
    Node* right;
public:
    Node();
//    ~Node();
};

class Tree {
    Node* root;
public:
    Tree();
//    ~Tree();
    Node* left_node();
    Node* right_node();
    void in_order_traversal( Node* node );
    void pre_order_traversal( Node* node );
    void post_order( Node* node );
    void breadth_first_traversal( Node* node);
};


void in_order_traversal( Node* node ) {
    if( node != NULL ) {
        print_person_data();
        
    }
}

void pre_order_traversal( Node* node ) {
    
}

void post_order( Node* node ) {
    
}

void breadth_first_traversal( Node* node) {
    
}
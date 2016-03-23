#pragma once

class Node {
    // Dawg dog what you doin? Use them templates
    void* data;
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
    Node* root_node();
    Node* left_node();
    Node* right_node();
    void in_order_traversal( Node* node );
    void pre_order_traversal( Node* node );
    void post_order( Node* node );
    void breadth_first_traversal( Node* node);
};

Node* Tree::left_node() {
    return left;
}

Node* Tree::right_node() {
    return right;
}


void Tree::pre_order_traversal( Node* node ) {
    if( node != NULL ) return;
    print_person_data();
    pre_order_traversal( node->left_node() );
    pre_order_traversal( node->right_node() );
}

void Tree::in_order_traversal( Node* node ) {
    if( node != NULL ) {
        in_order_traversal( node->left_node() );
        print_person_data();
        in_order_traversal( node->right_node() );
    }
}

void Tree::post_order_traversal( Node* node ) {
    if( node != NULL ) {
        post_order_traversal( node->left_node() );
        post_order_traversal( node->right_node() );
        print_person_data();
    }
}

void Tree::breadth_first_traversal( Node* node) {
    
}
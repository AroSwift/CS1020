#pragma once

//class Node {
//    // Dawg dog what you doin? Use them templates
//    void* data;
//    Node* left;
//    Node* right;
//public:
//    Node();
////    ~Node();
//};

class Tree {
    Tree *root;
    Tree *left;
    Tree *right;
public:
    Tree();
//    ~Tree();
    Tree* root_node();
    Tree* left_node();
    Tree* right_node();
    void in_order_traversal( Tree* node );
    void pre_order_traversal( Tree* node );
    void post_order_traversal( Tree* node );
    void breadth_first_traversal( Tree* node);
};

Tree* Tree::left_node() {
    return left;
}

Tree* Tree::right_node() {
    return right;
}


void Tree::pre_order_traversal( Tree* node ) {
    if( node != NULL ) return;
//    print_person_data();
    pre_order_traversal( node->left_node() );
    pre_order_traversal( node->right_node() );
}

void Tree::in_order_traversal( Tree* node ) {
    if( node != NULL ) {
        in_order_traversal( node->left_node() );
//        print_person_data();
        in_order_traversal( node->right_node() );
    }
}

void Tree::post_order_traversal( Tree* node ) {
    if( node != NULL ) {
        post_order_traversal( node->left_node() );
        post_order_traversal( node->right_node() );
//        print_person_data();
    }
}

void Tree::breadth_first_traversal( Tree* node) {
    
}



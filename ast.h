#pragma once

namespace ast {

    enum NodeType {
        IntegerNumber,
        Plus,
        Minus,
        Multiply,
        Divide
    };
    
    struct Node {
        NodeType type;
        Node* left;
        Node* right;
        int val;
    };
    
    Node* makeNode0 ( NodeType type ) {
        Node* nd = (Node*) malloc ( sizeof ( Node ) );
        nd->type  = type;
        nd->left  = NULL;
        nd->right = NULL;
        nd->val = 0;
        return nd;
    }
    
    Node* makeNode2 ( NodeType type, Node* left, Node* right ) {
        Node* nd = (Node*) malloc ( sizeof ( Node ) );
        nd->type  = type;
        nd->left  = left;
        nd->right = right;
        nd->val = 0;
        return nd;
    }

    void printNode ( const Node* n ) {
        switch ( n->type ) {
            case IntegerNumber:
                printf ( "%i", n->val );
                break;
            case Plus:
                printf ( " +" );
                break;
            case Minus:
                printf ( " -" );
                break;
            case Multiply:
                printf ( " *" );
                break;
            case Divide:
                printf ( " /" );
                break;
        }
        printf ( "\n" );

    }
    


    void print(const std::string& prefix, const Node* node, bool isLeft)
    {
        if( node != nullptr )
        {
            std::cout << prefix;
    
            std::cout << (isLeft ? "├──" : "└──" );
    
            // print the value of the node
            printNode ( node );
    
            // enter the next tree level - left and right branch
            print( prefix + (isLeft ? "│   " : "    "), node->left, true);
            print( prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }
    
    void print(const Node* node)
    {
        print("", node, false);    
    }
}

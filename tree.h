#ifndef TREE_H
#define TREE_H

#include "map.h"

typedef struct Node {
    int cost;
    t_soil soilType;


    struct Node* parent;
    struct Node* children[9];
    int numChildren;
} Node;


typedef struct s_Tree {
    Node* root;
} Tree;



Tree createEmptyTree();
Node* createNode(int cost, t_soil soilType);
void addChild(Node* parent, Node* child);
void displayTree(Node* node);
void freeTree(Node* node);

#endif //TREE_H

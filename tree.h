#ifndef TREE_H
#define TREE_H

#include "map.h"
#include "rover.h"
typedef struct Node {
    int cost;
    t_soil soilType;


    struct Node* parent;
    struct Node** children;
    int numChildren;
} Node;


typedef struct s_tree {
    Node* root;
} Tree;



Tree createEmptyTree();
Node* createNode(int x, int y, int cost, t_soil soilType);
void addChild(Node* parent, Node* child);
void displayTree(Node* node);
void createTree(t_map map, Tree tree, t_rover rover);
void createTreeRec(t_map map, Node* node, t_rover rover, int maxDepth);
void freeTree(Node* node);

#endif //TREE_H

#ifndef TREE_H
#define TREE_H

#include "map.h"

typedef struct {
    Node* root;
} Tree;

typedef struct Node {
    int x, y; // Position de MARC
    int cost;
    int totalCost;
    t_soil soilType;

    struct Node* parent;
    struct Node** childrens;
} Node;


#endif //TREE_H
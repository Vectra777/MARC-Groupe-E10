#include "tree.h"
#include "rover.h"
#include <stdlib.h>
#include <stdio.h>


Node* createNode(int cost, t_soil soilType) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->cost = cost;
    node->soilType = soilType;
    node->parent = NULL;
    node->children = NULL;
    node->numChildren = 0;
    return node;
}


void addChild(Node* parent, Node* child) {
    parent->numChildren++;
    parent->children = (Node**)realloc(parent->children, parent->numChildren * sizeof(Node*));
    parent->children[parent->numChildren - 1] = child;
    child->parent = parent;
}

void displayTree(Node* node) {
    printf("%d, Children: %d\n", node->cost, node->numChildren);
    for (int i = 0; i < node->numChildren; i++) {
        displayTree(node->children[i]);
    }
}

void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < node->numChildren; i++) {
        freeTree(node->children[i]);
    }
    free(node->children);
    free(node);
}

Tree createEmptyTree() {
    Tree tree;
    tree.root = NULL;
    return tree;
}






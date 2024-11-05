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

void createTree(t_map map, Tree tree, t_rover rover) {
    Node* root = createNode(map.costs[rover.pos.pos.x][rover.pos.pos.y], map.soils[rover.pos.pos.x][rover.pos.pos.y]);
    tree.root = root;
    createTreeRec(map, root, rover, 5, 0);
}

void createTreeRec(t_map map, Node* node, t_rover rover, int maxDepth, int availablemoves) {
    if (maxDepth == 0) {
        return;
    }
    for (int i = availablemoves; i < 9; i++) {
        t_localisation newPos = rover.pos;
        switch (rover.moves[i]) {
            case F_10:
                newPos = move(newPos,rover.moves[i]);
                break;
            case F_20:
                newPos = move(newPos,rover.moves[i]);
                break;
            case F_30:
                newPos = move(newPos,rover.moves[i]);
                break;
            case B_10:
                newPos = move(newPos,rover.moves[i]);
                break;
            case T_LEFT:
                newPos = move(newPos,rover.moves[i]);
                break;
            case T_RIGHT:
                newPos = move(newPos,rover.moves[i]);
                break;
            case U_TURN:
                newPos = move(newPos,rover.moves[i]);
                break;
            default:
                break;
        }
        if (isValidLocalisation(newPos.pos, map.x_max, map.y_max) && (newPos.pos.x != rover.pos.pos.x || newPos.pos.y != rover.pos.pos.y || newPos.ori != rover.pos.ori)) {
            Node* child = createNode(map.costs[newPos.pos.x][newPos.pos.y], map.soils[newPos.pos.x][newPos.pos.y]);
            addChild(node, child);
            rover.remainingMoves[i]--;
            createTreeRec(map, child, rover, maxDepth - 1, availablemoves+1);
            rover.remainingMoves[i]++;
        }
    }
}




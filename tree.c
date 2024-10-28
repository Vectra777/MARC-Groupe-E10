#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

Tree createTree() {
    Tree tree;
    tree.root = NULL;
    return tree;
}

Node* createNode(int x, int y, int cost, t_soil soilType) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->x = x;
    node->y = y;
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
    if (node == NULL) {
        return;
    }
    printf("Node (%d, %d) with cost %d and soil type %d\n", node->x, node->y, node->cost, node->soilType);
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

void MapToTreeRec(t_map map, Node* node, int** visited) {
    int x = node->x;
    int y = node->y;

    visited[y][x] = 1;

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int dir = 0; dir < 4; dir++) {
        int newX = x + dx[dir];
        int newY = y + dy[dir];

        if (newX >= 0 && newX < map.x_max && newY >= 0 && newY < map.y_max) {

            if (!visited[newY][newX]) {

                Node* child = createNode(newX, newY, map.costs[newY][newX], map.soils[newY][newX]);
                addChild(node, child);
                MapToTreeRec(map, child, visited);
            }
        }
    }
}


void MapToTree(t_map map, Tree* tree) {
    int x = rand() % map.x_max;
    int y = rand() % map.y_max;

    Node* root = createNode(x, y, map.costs[y][x], map.soils[y][x]);
    tree->root = root;

    // Initialize visited array
    int** visited = (int**)malloc(map.y_max * sizeof(int*));
    for (int i = 0; i < map.y_max; i++) {
        visited[i] = (int*)calloc(map.x_max, sizeof(int));
    }

    MapToTreeRec(map, root, visited);

    for (int i = 0; i < map.y_max; i++) {
        free(visited[i]);
    }
    free(visited);
}


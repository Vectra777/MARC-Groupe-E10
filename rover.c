#include "rover.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_rover createRover(t_localisation pos, int totalCost, Tree *tree)
{
    t_rover rover;
    rover.pos = pos;
    rover.totalCost = totalCost;
    int moves[] = {F_10, F_20, F_30, B_10, T_LEFT, T_RIGHT, U_TURN,F_30,F_30};
    memcpy(rover.moves, moves, sizeof(moves));
    rover.tree = *tree;
    int remainingMoves[] = {22, 15, 7, 7, 21, 21, 7};
    memcpy(rover.remainingMoves, remainingMoves, sizeof(remainingMoves));


    return rover;
}

void displayRover(t_rover rover)
{
    printf("Rover position: (%d, %d) %d\n", rover.pos.pos.x, rover.pos.pos.y, rover.totalCost);
    displayTree(rover.tree.root);
}

void freeRover(t_rover rover)
{
    freeTree(rover.tree.root);
}
void createTree(t_map map, Tree *tree, t_rover rover) {
    Node* root = createNode(map.costs[rover.pos.pos.x][rover.pos.pos.y], map.soils[rover.pos.pos.x][rover.pos.pos.y]);
    tree->root = root;
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
            createTreeRec(map, child, rover, maxDepth - 1, availablemoves+1);
        }
    }
}
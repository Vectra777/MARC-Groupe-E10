#include "rover.h"
#include "stack.h"
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
    rover.tree = tree;
    int remainingMoves[] = {22, 15, 7, 7, 21, 21, 7};
    memcpy(rover.remainingMoves, remainingMoves, sizeof(remainingMoves));


    return rover;
}

void displayRover(t_rover rover)
{
    printf("Rover position: (%d, %d) %d\n", rover.pos.pos.x, rover.pos.pos.y, rover.totalCost);
    displayTree(rover.tree->root);
}

void freeRover(t_rover rover)
{
    freeTree(rover.tree->root);
}
void createTree(t_map map, Tree *tree, t_rover rover) {
    Node* root = createNode(map.costs[rover.pos.pos.x][rover.pos.pos.y], map.soils[rover.pos.pos.x][rover.pos.pos.y]);
    tree->root = root;
    createTreeRec(map, root, rover, 5, 9);
}

void createTreeRec(t_map map, Node* node, t_rover rover, int maxDepth, int availablemoves) {
    if (maxDepth == 0) {
        return;
    }
    for (int i = 0; i < availablemoves; i++) {
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
        if (isValidLocalisation(newPos.pos, map.x_max, map.y_max)) {
            Node* child = createNode(map.costs[newPos.pos.x][newPos.pos.y], map.soils[newPos.pos.x][newPos.pos.y]);
            addChild(node, child);
            createTreeIterative(map, child, rover, maxDepth - 1, availablemoves-1);
        }
    }
}

void createTreeIterative(t_map map, Node* root, t_rover rover, int maxDepth, int availableMoves) {
    // Create a stack
    StackEntry* stack = (StackEntry*)malloc(sizeof(StackEntry) * 100); // Adjust size as needed
    int stackSize = 0;

    // Push the root node onto the stack
    stack[stackSize++] = (StackEntry){root, maxDepth, availableMoves};

    // Process the stack iteratively
    while (stackSize > 0) {
        // Pop a node from the stack
        StackEntry currentEntry = stack[--stackSize];
        Node* currentNode = currentEntry.node;
        int currentDepth = currentEntry.depth;
        int currentMoves = currentEntry.availableMoves;

        // If we've reached the maximum depth, continue
        if (currentDepth == 0) {
            continue;
        }

        // Try each move for the current node
        for (int i = 0; i < currentMoves; i++) {
            t_localisation newPos = rover.pos;
            newPos = move(newPos, rover.moves[i]);


            // Check if the new position is valid
            if (isValidLocalisation(newPos.pos, map.x_max, map.y_max)) {
                // Create a new child node
                Node* child = createNode(map.costs[newPos.pos.x][newPos.pos.y], map.soils[newPos.pos.x][newPos.pos.y]);
                addChild(currentNode, child);

                // Push the child node onto the stack with updated depth and moves
                stack[stackSize++] = (StackEntry){child, currentDepth - 1, currentMoves - 1};
            }
        }
    }

    // Free the stack memory
    free(stack);
}
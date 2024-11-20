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
void createTree(t_map *map, Tree *tree, t_rover rover) {
    Node* root = createNode(map->costs[rover.pos.pos.x][rover.pos.pos.y], map->soils[rover.pos.pos.x][rover.pos.pos.y], 0);
    tree->root = root;
    createTreeRec(map, root, rover, 5, 9);
}

void removeMove(t_rover *rover, int move) {
    int newMoves[9];
    int index = 0;
    for (int i = 0; i < 9; i++) {
        if (i != move) {
            newMoves[index] = rover->moves[i];
            index++;
        }
    }
    memcpy(rover->moves, newMoves, sizeof(newMoves));
}

void removeMoveByIndex(t_rover *rover, int totalMoves, int indexToRemove) {
    if (indexToRemove < 0 || indexToRemove >= totalMoves) {
        // Invalid index, do nothing
        fprintf(stderr, "Invalid index: %d\n", indexToRemove);
        return;
    }

    // Shift the remaining moves to fill the gap
    for (int i = indexToRemove; i < totalMoves - 1; i++) {
        rover->moves[i] = rover->moves[i + 1];
    }

    // Optionally, clear the last move (not strictly necessary, depends on your use case)
    rover->moves[totalMoves - 1] = 20;
}

void createTreeRec(t_map *map, Node* node, t_rover rover, int maxDepth, int availablemoves) {
    if (maxDepth == 0 || availablemoves <= 0) {
        return;
    }
    t_localisation initPos = rover.pos;
    for (int i = 0; i < availablemoves; i++) {

        t_localisation newPos = initPos;
        newPos = move(newPos, rover.moves[i]);

        if (isValidLocalisation(newPos.pos, map->x_max, map->y_max)) {

            if(map->soils[newPos.pos.x][newPos.pos.y] == CREVASSE){
                Node *child = createNode(map->costs[newPos.pos.x][newPos.pos.y], map->soils[newPos.pos.x][newPos.pos.y],
                                         rover.moves[i]);
                addChild(node, child);

            }else if(map->soils[newPos.pos.x][newPos.pos.y] == ERG){
                t_soil soilType = map->soils[newPos.pos.x][newPos.pos.y];
                Node *child = createNode(map->costs[newPos.pos.x][newPos.pos.y], soilType, rover.moves[i]);
                addChild(node, child);
                rover.pos = newPos;

                t_move tmpmoves[9];
                memcpy(tmpmoves, rover.moves, sizeof(rover.moves));

                // Reduce the effectiveness of movements based on rules
                int removedMovesCount = 0;
                for (int j = 0; j < 9; j++) {
                    switch (rover.moves[j]) {
                        case F_10:
                        case B_10:
                            rover.moves[j] = 0; // Disable this move
                            removedMovesCount++;
                            break;
                        case F_20:
                            rover.moves[j] = F_10; // Reduce advancing power
                            break;
                        case F_30:
                            rover.moves[j] = F_20; // Reduce advancing power
                            break;
                        case T_LEFT:
                        case T_RIGHT:
                            rover.moves[j] = 0; // Disable turning
                            removedMovesCount++;
                            break;
                        case U_TURN:
                            rover.moves[j] = T_LEFT; // Simplify the U-turn
                            break;
                        default:
                            break;
                    }
                }

                int newAvailableMoves = availablemoves - removedMovesCount;
                createTreeRec(map, child, rover, maxDepth - 1, newAvailableMoves);
                memcpy(rover.moves, tmpmoves, sizeof(tmpmoves));
            }else {
                Node *child = createNode(map->costs[newPos.pos.x][newPos.pos.y], map->soils[newPos.pos.x][newPos.pos.y],
                                         rover.moves[i]);
                addChild(node, child);
                rover.pos = newPos;
                t_move tmpmoves[9];
                memcpy(tmpmoves, rover.moves, sizeof(rover.moves));
                removeMoveByIndex(&rover, availablemoves, i);
                createTreeRec(map, child, rover, maxDepth - 1, availablemoves - 1);
                memcpy(rover.moves, tmpmoves, sizeof(tmpmoves));

            }

        }else{
            Node *child = createNode(11001, CREVASSE,
                                     rover.moves[i]);
            addChild(node, child);
        }
    }
}



Node* findLowestCostLeaf(Node* node) {

    if (node->numChildren == 0) {
        return node; // Return the cost of the leaf
    }

    // Recursively find the lowest cost in the child nodes
    int minCost = 99999;
    Node* minCostNode;
    for (int i = 0; i < node->numChildren; i++) {
        Node* childCost = findLowestCostLeaf(node->children[i]);
        if (childCost->cost < minCost && childCost->cost >= 0) {
            minCost = childCost->cost;
            minCostNode = childCost;
        }
    }

    return minCostNode;
}

int* retracePath(Node* node) {
    if (node == NULL) {
        printf("The node is NULL. No path to retrace.\n");
        return NULL;
    }

    Node* current = node;

    // Count the number of steps in the path
    int count = 0;
    int totalCost = 0;
    while (current->parent != NULL) {
        count++;
        current = current->parent;
    }

    // Allocate memory for the path (+1 to store the path length)
    int* path = (int*)malloc((count + 1) * sizeof(int));
    if (path == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Populate the path array and calculate the total cost
    current = node; // Reset current to the input node
    int index = 0;
    while (current->parent != NULL) {
        totalCost += current->cost;         // Add the cost of the current node
        path[index++] = current->move;     // Store the move
        current = current->parent;         // Move to the parent node
    }

    // Reverse the path to make it from root to node
    for (int i = 0; i < index / 2; i++) {
        int temp = path[i];
        path[i] = path[index - i - 1];
        path[index - i - 1] = temp;
    }

    //print path
    for (int i = 0; i < index; i++) {
        printf("%d ", path[i]);
    }

    int pathIndex = 0;
    // Retrace the path from the given node to the root
    while (current->parent != NULL) {
        totalCost += current->cost;          // Add the cost of the current node
        path[pathIndex++] = current->move;  // Store the move taken to reach this node
        current = current->parent;          // Move to the parent node
    }
    for (int i = 0; i < index / 2; i++) {
        int temp = path[i];
        path[i] = path[index - i - 1];
        path[index - i - 1] = temp;
    }
    path[pathIndex] = pathIndex;

    // Print the total cost
    printf("Total cost of the path: %d\n", totalCost);

    // Print the path in reverse order (from root to the given node)
    printf("Path (from root to node): ");
    for (int i = pathIndex - 1; i >= 0; i--) {
        if (path[i] != 0) { // Assuming 0 is a placeholder for no move
            printf("%d ", path[i]);
        }
    }
    printf("\n");
    return path;
}

void displayMapWithRover(t_map map, t_position roverPos) {
    for (int i = 0; i < map.y_max; i++) {
        for (int rep = 0; rep < 3; rep++) {
            for (int j = 0; j < map.x_max; j++) {
                char c[4];
                if (i == roverPos.y && j == roverPos.x) {
                    // Mark the rover's position with " x "
                    strcpy(c, " x ");
                } else {
                    switch (map.soils[i][j]) {
                        case BASE_STATION:
                            if (rep == 1) {
                                strcpy(c, " B ");
                            } else {
                                strcpy(c, "   ");
                            }
                            break;
                        case PLAIN:
                            strcpy(c, "---");
                            break;
                        case ERG:
                            strcpy(c, "~~~");
                            break;
                        case REG:
                            strcpy(c, "^^^");
                            break;
                        case CREVASSE:
                            sprintf(c, "%c%c%c", 219, 219, 219);
                            break;
                        default:
                            strcpy(c, "???");
                            break;
                    }
                }
                printf("%s", c);
            }
            printf("\n");
        }
    }
}

// Function to apply the path visually
void applyPath(t_map map, t_rover rover, t_move* path, int pathLength) {


    printf("Initial position:\n");
    displayMapWithRover(map, rover.pos.pos);
    printf("\n");


    printf("Final position reached.\n");
}

void guidance(t_rover rover, int* path) {
    int pathLength = path[-1];
    for (int i = 0; i < pathLength; i++) {
        t_move move1 = path[i];
        t_localisation newPos = move(rover.pos, move1);
        rover.pos = newPos;

        printf("Rover position: (%d, %d)\n", rover.pos.pos.x, rover.pos.pos.y);

    }
    printf("Final position reached.\n");
}


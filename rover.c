#include "rover.h"
#include <stdlib.h>
#include <stdio.h>

Rover createRover(t_localisation pos, int totalCost, Tree tree)
{
    Rover rover;
    rover.pos = pos;
    rover.totalCost = totalCost;
int moves[] = {F_10, F_20, F_30, B_10, T_LEFT, T_RIGHT, U_TURN};
memcpy(rover.moves, moves, sizeof(moves));
rover.tree = tree;
int remainingMoves[] = {22, 15, 7, 7, 21, 21, 7};
memcpy(rover.remainingMoves, remainingMoves, sizeof(remainingMoves));


    return rover;
}

void displayRover(Rover rover)
{
    printf("Rover position: (%d, %d) %d\n", rover.pos.pos.x, rover.pos.pos.y, rover.totalCost);
    displayTree(rover.tree.root);
}

void freeRover(Rover rover)
{
    freeTree(rover.tree.root);
}
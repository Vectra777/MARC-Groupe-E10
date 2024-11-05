#ifndef ROVER_H
#define ROVER_H

#include "map.h"
#include "tree.h"
#include "loc.h"
#include "moves.h"

//create a rover structure
typedef struct s_rover
{
    t_localisation pos;
    int totalCost;
    //array of moves
    t_move moves[9];
    Tree tree;
    int remainingMoves[7];
} Rover;

Rover createRover(t_localisation, int, t_move, Tree);
void displayRover(Rover);
void freeRover(Rover);

#endif //ROVER_H
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
    Tree *tree;
} t_rover;

t_rover createRover(t_localisation loc, int totalCost, Tree *tree);
void displayRover(t_rover);
void freeRover(t_rover);
void removeMove(t_rover* , int move);
void createTree(t_map *map, Tree *tree, t_rover rover);
void createTreeRec(t_map *map, Node* node, t_rover rover, int maxDepth, int availablemoves);
Node* findLowestCostLeaf(Node* node);
int* retracePath(Node* node);
void applyPath(t_map map, t_rover rover, t_move* path, int pathLength);
void displayMapWithRover(t_map map, t_position roverPos);
void guidance(t_rover rover, int* path);
void getmouves(int tab[]);

#endif //ROVER_H

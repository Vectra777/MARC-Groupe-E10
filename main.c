#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include <stdbool.h>
#include <time.h>
#include "rover.h"


 int main() {

    t_map map = createMapFromFile("..\\maps\\example1.map");
    // create a test for a rover with a tree
    Tree tree = createEmptyTree();

    //create random loc init that is in the map
     srand(time(NULL)); // Seed the random number generator

     int x = rand() % map.x_max;
     int y = rand() % map.y_max;

     t_localisation init =loc_init(x, y, NORTH);

    t_rover rover = createRover(init, 0, &tree);
    createTree(&map, &tree, rover);
    Node* lowestcost= findLowestCostLeaf(tree.root);
    int* path = retracePath(lowestcost);
    applyPath(map, rover, path, path[-1]);



    freeRover(rover);

    
    return 0;
}



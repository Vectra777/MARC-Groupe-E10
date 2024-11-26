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

     int x = rand()%map.x_max;
     int y = rand()%map.y_max;
     if (map.soils[x][y] == CREVASSE) {
         printf("The rover crosses to a crevasse\n");
         printf("Marc falls and dies.\n");
         return 0;
     }


     t_localisation init =loc_init(x, y, NORTH);
     t_rover rover = createRover(init, 0, &tree, 5);
    createTree(&map, &tree, rover);
    Node* lowestcost= findLowestCostLeaf(tree.root);
    int* path = retracePath(lowestcost, &rover);

    guidance(rover, path, map);




    freeRover(rover);

    return 0;
}



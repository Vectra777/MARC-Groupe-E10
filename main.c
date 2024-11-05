#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include <stdbool.h>
#include "rover.h"


 int main() {
 /*   
    ;
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    */
/*salut*/
   
    t_map map = createMapFromFile("..\\maps\\example1.map");
    // create a test for a rover with a tree
    Tree tree = createEmptyTree();
    t_rover rover = createRover(loc_init(5, 5, NORTH), 0,tree);
    createTree(map, tree, rover);
    displayRover(rover);
    displayTree(tree.root);
    
    return 0;
}



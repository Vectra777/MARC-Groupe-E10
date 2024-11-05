#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "tree.h"
#include <stdbool.h>


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

   
    t_map map = createMapFromFile("..\\maps\\example1.map");

    return 0;
}



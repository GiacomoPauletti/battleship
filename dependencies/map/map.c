#include <stdio.h>
#include "map.h"

void empty(Map map)
{
    int cursorX, cursorY;
    for (cursorY = 0; cursorY < MAP_HEIGHT; cursorY++)
    {
        for (cursorX = 0; cursorX < MAP_WIDTH; cursorX++)
        {
            map[cursorY][cursorX] = EMPTY_CHAR;
        }

    }

}

void add(Map map, Coordinate coord, char symbol)
{
    map[coord.y][coord.x] = symbol;
}

void printMap(Map map)
{
    int cursorX, cursorY;
    for (cursorY = 0; cursorY < MAP_HEIGHT; cursorY++)
    {
        printf("\n\n\n\t\t\t");
        for (cursorX = 0; cursorX < MAP_WIDTH; cursorX++)
        {
            printf("      %c", map[cursorY][cursorX]);
        }

    }
    printf("\n");

    
}

#include <stdio.h>
#include "map.h"

int MAP_WIDTH = DEFAULT_MAP_WIDTH;
int MAP_HEIGHT = DEFAULT_MAP_HEIGHT;

void empty(Map map)
{
    int cursorX, cursorY;
    for (cursorY = 0; cursorY < MAP_HEIGHT; cursorY++)
    {
        for (cursorX = 0; cursorX < MAP_WIDTH; cursorX++)
        {
            map[cursorY][cursorX] = EMPTY_CHAR;     //might be changed to addToMap
        }

    }

}

void addToMap(Map map, Coordinate coord, char symbol)
{
    map[coord.y][coord.x] = symbol;
}

void mAddToMap(Map map, Coordinate *coord, int length, char symbol)
{
    int cursor;

    for ( cursor = 0; cursor < length; cursor++ )
    {
        map[coord[cursor].y][coord[cursor].x] = symbol;
    }
}

char getFromMap(Map map, Coordinate coord)
{
    return map[coord.y][coord.x];
}

void printMap(Map map)
{
    int cursorX, cursorY;
    for (cursorY = 0; cursorY < MAP_HEIGHT; cursorY++)
    {
        printf("\n\n\n\t\t\t");
        for (cursorX = 0; cursorX < MAP_WIDTH; cursorX++)
        {
            printf("      %c", map[cursorY][cursorX]);  //might be changed to getFromMap
        }

    }
    printf("\n");

    
}

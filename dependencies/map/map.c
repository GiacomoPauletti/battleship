#include <stdio.h>
#include "map.h"

int MAP_WIDTH = DEFAULT_MAP_WIDTH;
int MAP_HEIGHT = DEFAULT_MAP_HEIGHT;

void empty(MapWrap *map)
{
    int cursorX, cursorY;
    for (cursorY = 0; cursorY < map -> dims.y; cursorY++)
    {
        for (cursorX = 0; cursorX < map -> dims.x; cursorX++)
        {
            map -> map[cursorY][cursorX] = EMPTY_CHAR;     //might be changed to addToMap
        }

    }

}

char getFromMap(MapWrap map, Coordinate coord)
{
    return map.map[coord.y][coord.x];
}

void addToMap(MapWrap *map, Coordinate coord, char symbol)
{
    map -> map[coord.y][coord.x] = symbol;
}

void mAddToMap(MapWrap *map, Coordinate *points, int length, char symbol)
{
    int cursor;

    for ( cursor = 0; cursor < length; cursor++ )
    {
        map -> map[points[cursor].y][points[cursor].x] = symbol;
    }
}


void printMap(MapWrap map)
{
    int cursorX, cursorY;
    for (cursorY = 0; cursorY < map.dims.y; cursorY++)
    {
        printf("\n\n\n\t\t\t");
        for (cursorX = 0; cursorX < map.dims.x; cursorX++)
        {
            printf("      %c", map.map[cursorY][cursorX]);  //might be changed to getFromMap
        }

    }
    printf("\n");

    
}

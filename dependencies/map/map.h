#include <stdio.h>

#define DEFAULT_MAP_WIDTH 8
#define DEFAULT_MAP_HEIGHT 8

#define EMPTY_CHAR '.'
#define HIT_SHIP_CHAR 'X'
#define SAFE_SHIP_CHAR 'O'


#if !defined(MAP_H)
#define MAP_H
typedef struct
{
    int x;
    int y;

} Coordinate;

typedef char Map[DEFAULT_MAP_HEIGHT][DEFAULT_MAP_WIDTH];

int MAP_WIDTH = DEFAULT_MAP_WIDTH;
int MAP_HEIGHT = DEFAULT_MAP_HEIGHT;

void empty(Map map);

void add(Map map, Coordinate coord, char symbol);

void printMap(Map map);
#endif
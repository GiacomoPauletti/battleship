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

typedef struct
{
    Map map;
    Coordinate dims;
}MapWrap;

extern int MAP_WIDTH;
extern int MAP_HEIGHT;

void empty(MapWrap map);

char getFromMap(MapWrap map, Coordinate coord);

void addToMap(MapWrap map, Coordinate coord, char symbol);

void mAddToMap(MapWrap map, Coordinate *points, int length, char symbol);

void printMap(MapWrap map);

#endif
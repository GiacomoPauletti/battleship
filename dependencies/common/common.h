#include <stdlib.h>
#include "../map/map.h"
#include "../ship/ship.h"

#if !defined(COMMON_H)
#define COMMON_H
#define MAX_NAME_LENGTH 20
/* maximum length of player name */

#define WIN_SIZE 120

typedef struct
{
    char name[MAX_NAME_LENGTH + 1];
    MapWrap defenceMap;
    MapWrap attackMap;

    Ship ships[MAX_SHIP_NUM];
    int shipNumber;

    int winner;

} Player;

typedef struct
{
    char safe_ship_symbol;
    char hit_ship_symbol;
    char empty_symbol;
} Settings;

int clearScreen();

char getch_();

int printCenter(char string[]);

int printnlnCenter(char string[]);

int MultiPrintCenter(char string[]);

void filterNewLine(char string[]);

void gameWinWriting();
void gameLostWriting();

#endif
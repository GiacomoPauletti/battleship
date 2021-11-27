#include <stdio.h>
#include "../map/map.h"
#include "../ship/ship.h"

#if !defined(MENU_H)
#define MENU_H

#define MAX_NAME_LENGTH 20
/* maximum length of player name */

typedef struct
{
    char name[MAX_NAME_LENGTH + 1];
    Map defenceMap;
    Map attackMap;

    Ship ships[MAX_SHIP_NUM];
    int shipNumber;

} Player;

typedef struct {} MenuData;

#endif